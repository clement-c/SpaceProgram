#include <iostream>
#include <cmath>

#include <glad/gl.h>

#include <Engine/Core/Application.hpp>

#include <Engine/Graphics/GL/GLProgram.hpp>
#include <Engine/Graphics/GL/GLBuffer.hpp>
#include <Engine/Graphics/GL/GLVAO.hpp>

int main(int argc, char** argv)
{
    Application app{argc, argv};

    // CC_LOG_INFO("Creating window...\n");
    auto const mainWindowId = app.NewWindow(1920, 1080, "OGLTriangleWindow");
    WindowsManager& winManager = app.GetWindowsManager();
    winManager.CenterWindow(mainWindowId);
    winManager.MakeWindowCurrent(mainWindowId);

    // Upload the vertices data to a VBO
    float vertData[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    GLBuffer vbo(GLBuffer::Type::kArrayBuffer);
    vbo.SetData(vertData, sizeof(vertData), GL_STATIC_DRAW);

    // Register the buffers and their layouts in a VAO
    GLVAO triangleVAO(vbo, {
        { 0, {3, GL_FLOAT, false, (int)(3 * sizeof(float)), (void*)(0)} }
    });

    GLProgram program;
    program.Link(); // Will set and compile the default shaders if none were provided

    glViewport(0, 0, 1920, 1080);

    // double fps = 0.0f;
    // double prevSec = 0.0;
    auto loop = [&](Application& app, double timeSec) -> int {
        // double timeSec = timeMs * 1.0e-3;
        // fps = 1.0 / (timeSec - prevSec);
        // prevSec = timeSec;
        for (auto i = 0; i < winManager.GetNumWindows(); i++)
        {
            winManager.MakeWindowCurrent(i);

            glClearColor((sin(timeSec) * 0.5 + 0.5), 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);

            program.Use();

            triangleVAO.Draw(GLVAO::DrawType::kTriangles); // Binds automatically

            winManager.SwapBuffers();
        }
        return 0;
    };
    app.SetLoop(loop);

    return app.Run();
}
