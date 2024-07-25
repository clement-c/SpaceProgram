#include <Engine/Core/Application.hpp>
#include <Engine/Core/Window.hpp>
#include <Engine/Core/Logging.hpp>
#include <Engine/Core/System/Path.hpp>
#include <Engine/Scene.hpp>

#include <Engine/Runtime/Camera.hpp>
#include <Engine/Core/Maths/MathsIO.hpp>

#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


bool LoadObj(char const *path, std::vector<TriangulatedMesh> &outMeshes)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool status = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path, nullptr, true); // path.Filename().ToString().c_str(), path.Directory().ToString().c_str(), true);
    if (!err.empty())
    {
        CC_LOG_ERROR(err);
    }
    if (!status)
        return false;

    size_t max_vtx_count = 0;
    for (size_t s = 0; s < shapes.size(); s++)
    {
        auto curr_num_face_vertices = shapes[s].mesh.num_face_vertices.size() * 3;
        max_vtx_count = curr_num_face_vertices > max_vtx_count ? curr_num_face_vertices : max_vtx_count;
    }
    
    // reserve buffer for larger
    std::vector<float> mesh_data(max_vtx_count * 8);

    outMeshes.clear();
    for (size_t s = 0; s < shapes.size(); s++)
    {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        size_t num_verts = shapes[s].mesh.indices.size();

        // for each face (triangles as we force triangulation on import)
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            // int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < 3; v++)
            {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                auto offset = (f * 3 + v) * 8;
                mesh_data[offset] = attrib.vertices[3 * idx.vertex_index + 0];
                mesh_data[offset + 1] = attrib.vertices[3 * idx.vertex_index + 1];
                mesh_data[offset + 2] = attrib.vertices[3 * idx.vertex_index + 2];

                mesh_data[offset + 3] = attrib.texcoords[2 * idx.texcoord_index + 0];
                mesh_data[offset + 4] = attrib.texcoords[2 * idx.texcoord_index + 1];

                mesh_data[offset + 5] = attrib.normals[3 * idx.normal_index + 0];
                mesh_data[offset + 6] = attrib.normals[3 * idx.normal_index + 1];
                mesh_data[offset + 7] = attrib.normals[3 * idx.normal_index + 2];
            }
            index_offset += 3;
        }

        auto &mesh = outMeshes.emplace_back();
        mesh.SetData(mesh_data.data(), num_verts);
    }

    return status;
}

int main(int argc, char **argv)
{
    int const WIN_WIDTH = 1920 * 0.75, WIN_HEIGHT = 1080 * 0.75;

    Application app(argc, argv);

    // Initialize engine with default systems
    auto &engine = app.GetEngine();
    if (!engine.Initialize())
    {
        CC_LOG_ERROR("Engine could not initialize.");
        return -1;
    }
    std::cout << app.GetPath().ToString() << std::endl;

    // Open a new window and center it
    Window *const main_window = app.NewWindow(WIN_WIDTH, WIN_HEIGHT, "Deliverable 03 - ObjViewer");

    // Load model
    std::vector<TriangulatedMesh> model;
    LoadObj("rsc03/scene.obj", model);

    // Upload mesh
    auto &renderer = main_window->GetRenderer();
    int32_t model_id = renderer.Upload(model[0]);

    // Set Camera
    Camera camera;
    Vector4 mesh_center = model[0].GetCenter();
    Matrix44 camMatrix = Matrix44::FromPosition(0.0, mesh_center.y, 7.0);
    camera.SetViewMatrix(camMatrix.InverseOrthonormal());
    renderer.UpdateCamera(camera);

    auto loop = [&camera, &renderer, &camMatrix, model_id](Application &app, double timeSec) -> int {
        Matrix44 rotation = Matrix44(Matrix33::RotationY(static_cast<float>(timeSec * -0.5)));
        renderer.TransformEntity(model_id, rotation);
        return 0;
    };
    app.SetLoop(loop);

    return app.Run();
}
