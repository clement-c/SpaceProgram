#pragma once
#include <string>
#include <functional>

#include "Engine/Renderer.hpp"
#include "Engine/Core/Events/KeyboardEvent.hpp"
#include "Lib.hpp"

struct GLFWwindow;
struct WindowsManager;

struct Window
{
    Window(GLFWwindow *ptr);

    DLLEXPORT bool SetTitle(std::string const &title);

    DLLEXPORT bool GetSize(int *width, int *height) const noexcept;
    DLLEXPORT bool GetSize(float size[2]) const noexcept;

    DLLEXPORT Renderer &GetRenderer();

    DLLEXPORT bool IsKeyPressed(KeyboardEvent::Key) const noexcept;

    GLFWwindow *GlfwPtr();

    friend struct WindowsManager;

private:
    void WindowResized(int width, int height);

    GLFWwindow *m_ptr;
    Renderer m_renderer;
};
