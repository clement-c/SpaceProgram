#include "Engine/Core/WindowsManager.hpp"
#include "Engine/Core/Window.hpp"
#include "Engine/Core/Logging.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

WindowsManager::WindowsManager() {}

WindowsManager::~WindowsManager()
{
	if (initialized)
		glfwTerminate();
}

bool WindowsManager::Initialize()
{
	CC_LOG_DEBUG("Initializing glfw...\n");
	initialized = glfwInit();

	if (!initialized)
	{
		CC_LOG_DEBUG(" ... initializing glfw FAILED\n");
		return false;
	}

	// TODO: Move to renderer (OpenGL impl)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	CC_LOG_DEBUG(" ... initializing glfw SUCCEEDED\n");

	return true;
}

void WindowsManager::ProcessEvents()
{
	if (initialized)
		glfwPollEvents();

	// If windows should close, close
}

Window *WindowsManager::GetWindow(size_t winId) const
{
	if (winId < 0 || winId < (m_windows.size() - 1))
		return nullptr;
	return m_windows.at(winId).get();
}

WindowsManager::operator bool()
{
	return initialized;
}

Window *const WindowsManager::NewWindow()
{
	auto *ptr = NewWindow(1280, 720, "Untitled");
	return ptr;
}

Window *const WindowsManager::NewWindow(uint32_t const w, uint32_t const h)
{
	auto *ptr = NewWindow(w, h, "Untitled window");
	return ptr;
}

Window *const WindowsManager::NewWindow(uint32_t const w, uint32_t const h, std::string const &title)
{
	if (!initialized)
		if (!Initialize())
		{
			CC_LOG_ERROR("Could not initialize glfw in WindowsManager::NewWindow\n");
		}

	GLFWwindow *ptr = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
	if (!ptr)
		return nullptr;

	glfwMakeContextCurrent(ptr);

	// TODO: Move to OpenGL impl
	if (!m_gladInitialized)
	{
		CC_LOG_DEBUG("Initializing Glad interface...\n");
		int version = gladLoadGL(glfwGetProcAddress);
		while (GL_NO_ERROR != glGetError())
		{
		}
		CC_LOG_SUCCESS("Loaded OpenGL {}.{}\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

		if (version = 0)
		{
			CC_LOG_ERROR("Failed to create a window as GLAD could not initialize\n");
			return nullptr;
		}
		else
		{
			CC_LOG_SUCCESS("Glad successfully initialized\n");
		}
		m_gladInitialized = true;
	}

	auto winId = m_windows.size();
	auto &win_ptr = m_windows.emplace_back(std::make_unique<Window>(ptr));

	glfwSetInputMode(ptr, GLFW_STICKY_KEYS, GLFW_TRUE);

	glfwSetWindowSizeCallback(ptr, [](GLFWwindow *window, int width, int height)
							  { reinterpret_cast<Window *>(glfwGetWindowUserPointer(window))->WindowResized(width, height); });

	glfwSetKeyCallback(ptr, [](GLFWwindow *w, int key, int scancode, int action, int mods)
					   { CC_LOG_INFO("--> Key {}\n", key); }); // WindowsEventsManager::KeyCallback); // [](GLFWwindow* w, int key, int scancode, int action, int mods){ CC_LOG_INFO("--> Key {}\n", key); });

	// glfwSetCharCallback(ptr, [](GLFWwindow*, unsigned int codepoint) { CC_LOG_DEBUG("Char callback {}\n", codepoint); });
	// glfwSetMouseButtonCallback(ptr, WindowsEventsManager::MouseButtonCallback);
	// glfwSetCursorPosCallback(ptr, WindowsEventsManager::CursorPosCallback);
	// glfwSetCursorEnterCallback(ptr, WindowsEventsManager::CursorEnterCallback);
	// glfwSetScrollCallback(ptr, WindowsEventsManager::ScrollCallback);
	// glfwSetDropCallback(ptr, WindowsEventsManager::DropCallback);
	// glfwSetWindowPosCallback(ptr, WindowsEventsManager::WindowPosCallback);
	// glfwSetWindowSizeCallback(ptr, WindowsEventsManager::WindowSizeCallback);
	// glfwSetWindowCloseCallback(ptr, WindowsEventsManager::WindowCloseCallback);

	return m_windows.at(winId).get();
}

int WindowsManager::GetNumMonitors() const
{
	int result = 0;
	glfwGetMonitors(&result);
	return result;
}

size_t WindowsManager::GetNumWindows() const
{
	return m_windows.size();
}

bool WindowsManager::MakeWindowCurrent(size_t winId) const
{
	if (winId < GetNumWindows())
	{
		glfwMakeContextCurrent(m_windows.at(winId)->GlfwPtr());
		return true;
	}
	return false;
}

bool WindowsManager::SwapBuffers(size_t winId) const
{
	glfwSwapBuffers(m_windows.at(winId)->GlfwPtr());
	return true;
}

bool WindowsManager::CloseWindow(size_t winId) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		glfwSetWindowShouldClose(m_windows.at(winId)->GlfwPtr(), GLFW_TRUE);
		return true;
	}
	return true;
}

bool WindowsManager::WindowShouldClose(size_t winId) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		return glfwWindowShouldClose(m_windows.at(winId)->GlfwPtr());
	}
	else
		return false;
}

bool WindowsManager::SetWindowTitle(size_t winId, std::string const &title) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		glfwSetWindowTitle(m_windows.at(winId)->GlfwPtr(), title.c_str());
		return true;
	}
	else
		return false;
}

bool WindowsManager::SetWindowFullscreen(size_t winId, bool, uint8_t screenId) const
{
	if (winId < m_windows.size() && m_windows.at(winId)->GlfwPtr() != nullptr)
	{
		CC_LOG_ERROR("SetWindowFullscreen is not implemented yet.");
		return true;
	}
	else
		return false;
}

bool WindowsManager::SetWindowSize(size_t winId, uint32_t w, uint32_t h) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		glfwSetWindowSize(m_windows.at(winId)->GlfwPtr(), w, h);
		return true;
	}
	else
		return false;
}

bool WindowsManager::CenterWindow(uint32_t winId, uint8_t screenId) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();

		int monitorsCount;
		GLFWmonitor **monitors = glfwGetMonitors(&monitorsCount);
		if (screenId > (static_cast<uint32_t>(monitorsCount) - 1))
		{
			CC_LOG_ERROR("Only found {} screens, cannot center window on screen #{}\n", monitorsCount, screenId);
			return false;
		}

		GLFWwindow *window = m_windows.at(winId)->GlfwPtr();

		int mx, my, mw, mh;
		glfwGetMonitorWorkarea(monitor, &mx, &my, &mw, &mh);

		int ww, wh;
		glfwGetWindowSize(window, &ww, &wh);
		glfwSetWindowPos(window, static_cast<int>((mw - ww) * 0.5), static_cast<int>((mh - wh) * 0.5));
		return true;
	}
	else
		return false;
}

bool WindowsManager::SetWindowTopLeftCorner(size_t winId, uint32_t x, uint32_t y, uint8_t screenId) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		GLFWwindow *window = m_windows.at(winId)->GlfwPtr();
		glfwSetWindowPos(window, x, y);
		return true;
	}
	else
		return false;
}
