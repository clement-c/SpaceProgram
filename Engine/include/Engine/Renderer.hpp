#pragma once

#include <memory>
#include <vector>
#include <stdint.h>

#include "Core/Lib.hpp"
#include "Core/Color.hpp"
#include "Runtime/Material.hpp"
#include "Graphics/RendererBackendI.hpp"

// Manipulated objects
struct Camera;
struct Matrix44;
struct TriangulatedMesh;


/**
 * @brief One renderer per window/context
 *
 */
class Renderer
{
public:
    enum class API
    {
        kVulkan,
        kOpenGL45,
        kDirect3D12
    };

    struct RenderOptions
    {
        Color clear_color;
    };

    /**
     * @brief Checks whether the engine was compiled with support for a given API
     *
     * @param api
     * @return true
     * @return false
     */
    DLLEXPORT static bool RendererImplements(API api);

    /**
     * @brief Check whether the current host supports a given graphics API
     *
     * @param api
     * @return true
     * @return false
     */
    DLLEXPORT static bool HostSupports(API api);

    /**
     * @brief
     *
     * @param api
     * @return true
     * @return false
     */
    DLLEXPORT bool Initialize(API api = API::kOpenGL45);
    DLLEXPORT bool IsInitialized() const { return m_backend != nullptr; }
    DLLEXPORT void Shutdown();
    // DLLEXPORT void Restart() { Shutdown(); Initialize(); }

    // Materials
    Material &DefaultMaterial() const;
    // Material &NewMaterial(Material::Type);
    bool BindMaterial(Material const &);

    // Managing meshes
    DLLEXPORT int32_t UploadMesh(TriangulatedMesh const &);

    /** TODO: Move to "Renderable" Entity */
    DLLEXPORT bool TransformItem(int32_t mesh_gpu_id, Matrix44 const &transform);
    DLLEXPORT bool DisableItem(uint32_t mesh_gpu_id);
    DLLEXPORT bool DeleteItem(uint32_t mesh_gpu_id);

    // Render geometries
    // Simplified, need to allow options for depthbuffer clearing for example, and render subset of items
    DLLEXPORT bool RenderAll() const;
    DLLEXPORT bool Render(/* items, material, RenderSurface& render_surface, RenderOptions conts& options */) const;

    // Camera utils
    DLLEXPORT bool UpdateCamera(Camera const &) noexcept;
    void SetViewport(int width, int height) noexcept;

private:
    std::unique_ptr<RendererBackendI> m_backend = nullptr;
};
