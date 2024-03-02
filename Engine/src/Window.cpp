#include "Engine/Core/Window.hpp"
#include "Engine/Core/Logging.hpp"

#include <GLFW/glfw3.h>

Window::Window(GLFWwindow *ptr) : m_ptr{ptr}
{
	glfwSetWindowUserPointer(ptr, reinterpret_cast<void *>(this));

	if (!m_renderer.Initialize()) // TODO: Get renderer from static attribute of Renderer defining preferred api
		CC_LOG_ERROR("Could not initialize the renderer on new window");

	int w, h;
	GetSize(&w, &h);
	WindowResized(w, h);
}

bool Window::SetTitle(std::string const &title)
{
	if (m_ptr)
	{
		glfwSetWindowTitle(m_ptr, title.c_str());
		return true;
	}
	return false;
}

bool Window::GetSize(int *width, int *height) const noexcept
{
	if (m_ptr)
	{
		glfwGetWindowSize(m_ptr, width, height);
		return true;
	}
	else
	{
		return false;
	}
}

bool Window::IsKeyPressed(KeyboardEvent::Key key) const noexcept
{
	if(m_ptr)
	{
		auto state = glfwGetKey(m_ptr, static_cast<int32_t>(key));
		return state == GLFW_PRESS;
	}
	return false;
}


GLFWwindow *Window::GlfwPtr()
{
	return m_ptr;
}

Renderer &Window::GetRenderer()
{
	return m_renderer;
}

void Window::WindowResized(int width, int height)
{
	m_renderer.SetViewport(width, height);
}
