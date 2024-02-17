#pragma once
#include <string>
#include <functional>

#include "Lib.hpp"

struct GLFWwindow;
struct Renderer;

struct Window
{
    using RenderFunctionType = std::function<bool(Window const &)>; //, Renderer&)>;

    Window(GLFWwindow *ptr);

    DLLEXPORT bool SetTitle(std::string const &title);

    DLLEXPORT bool GetSize(int *width, int *height) const noexcept;

    // Most likely will only be used for early deliverables before rendering and scene graph are their own systems
    DLLEXPORT bool SetCustomRenderFunction(RenderFunctionType &&function) noexcept;
    DLLEXPORT RenderFunctionType GetCustomRenderFunction() const noexcept;

    GLFWwindow *GlfwPtr();

private:
    GLFWwindow *m_ptr;
    RenderFunctionType m_render_function = nullptr;
};
