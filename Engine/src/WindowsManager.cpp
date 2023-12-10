#include "Engine/Core/WindowsManager.hpp"
#include "Engine/Core/Logging.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>


class EventsManager
{
public:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		CC_LOG_INFO("Key event: {}\n", key);
	}

	static void CharCallback(GLFWwindow* window, unsigned int codepoint)
	{
		CC_LOG_INFO("Char callback: {}\n", codepoint);
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		CC_LOG_INFO("Mouse Button callback: {}/{}/{}\n", button, action, mods);
	}

	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		CC_LOG_INFO("Cursor pos callback: {}/{}\n", xpos, ypos);
	}

	static void CursorEnterCallback(GLFWwindow* window, int entered)
	{
		CC_LOG_INFO("Mous enter callback {}\n", entered);
	}

	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		CC_LOG_INFO("Mouse enter callback {}/{}\n", xoffset, yoffset);
	}

	static void DropCallback(GLFWwindow* window, int path_count, const char* paths[])
	{
		CC_LOG_INFO("Drop callback {}\n", path_count);
	}

	static void WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		CC_LOG_INFO("Drop callback {}/{}\n", width, height);
	}

	static void WindowPosCallback(GLFWwindow* window, int xpos, int ypos)
	{
		CC_LOG_INFO("Window pos callback {}/{}\n", xpos, ypos);
	}

	static void WindowCloseCallback(GLFWwindow* window)
	{
		CC_LOG_INFO("Window close callback\n");
	}

};

WindowsManager::WindowsManager()
{
}

WindowsManager::~WindowsManager() {
	if (initialized) glfwTerminate();
}

bool WindowsManager::Initialize()
{
	CC_LOG_DEBUG("Initializing glfw...\n");
	initialized = glfwInit();

	if (!initialized) {
		CC_LOG_DEBUG(" ... initializing glfw FAILED\n");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	CC_LOG_DEBUG(" ... initializing glfw SUCCEEDED\n");
	return true;
}

void WindowsManager::ProcessEvents()
{
	if (initialized) glfwPollEvents();

	// If windows should close, close
}

WindowsManager::operator bool()
{
	return initialized;
}

void* const WindowsManager::NewWindow()
{
	// TODO: share resource if second window
	auto* ptr = NewWindow(1280, 720, "Untitled");
	return ptr;
}

void* const WindowsManager::NewWindow(uint32_t const w, uint32_t const h)
{
	// TODO: share resource if second window
	auto* ptr = NewWindow(w, h, "Untitled window");
	return ptr;
}

void* const WindowsManager::NewWindow(uint32_t const w, uint32_t const h, std::string const& title)
{
	if (!initialized) if (!Initialize()) {
		CC_LOG_ERROR("Could not initialize glfw in WindowsManager::NewWindow\n");
	}

	// TODO: share resource if second window
	auto* ptr = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
	if (!ptr) return nullptr;

	auto winId = m_windows.size();
	m_windows.push_back(ptr);

	glfwMakeContextCurrent(ptr);

	if (!m_gladInitialized)
	{
		int version = gladLoadGL(glfwGetProcAddress);
		while (GL_NO_ERROR != glGetError()) {}
		CC_LOG_SUCCESS("Loaded OpenGL {}.{}\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

		if (version = 0) {
			CC_LOG_ERROR("Failed to create a window as GLAD could not initialize\n");
			return nullptr;
		}
		else {
			CC_LOG_SUCCESS("Glad successfully initialized\n");
		}
		m_gladInitialized = true;
	}

	glfwSetKeyCallback(ptr, [](GLFWwindow* w, int key, int scancode, int action, int mods){ CC_LOG_INFO("--> Key {}\n", key); });
	glfwSetCharCallback(ptr, EventsManager::CharCallback);
	glfwSetMouseButtonCallback(ptr, EventsManager::MouseButtonCallback);
	glfwSetCursorPosCallback(ptr, EventsManager::CursorPosCallback);
	glfwSetCursorEnterCallback(ptr, EventsManager::CursorEnterCallback);
	glfwSetScrollCallback(ptr, EventsManager::ScrollCallback);
	glfwSetDropCallback(ptr, EventsManager::DropCallback);
	glfwSetWindowPosCallback(ptr, EventsManager::WindowPosCallback);
	glfwSetWindowSizeCallback(ptr, EventsManager::WindowSizeCallback);
	glfwSetWindowCloseCallback(ptr, EventsManager::WindowCloseCallback);

	return ptr;
}


size_t WindowsManager::NumWindows() const
{
	return m_windows.size();
}


bool WindowsManager::MakeWindowCurrent(size_t winId) const
{
	if(winId < NumWindows())
	{
		glfwMakeContextCurrent((GLFWwindow*)m_windows.at(winId));
		return true;
	}
	return false;
}


bool WindowsManager::SwapBuffers(size_t winId) const
{
	glfwSwapBuffers((GLFWwindow*)m_windows.at(winId));
	return true;
}


bool WindowsManager::CloseWindow(size_t winId) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		glfwSetWindowShouldClose((GLFWwindow*)m_windows.at(winId), GLFW_TRUE);
		return true;
	}
	return true;
}


bool WindowsManager::WindowShouldClose(size_t winId) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		return glfwWindowShouldClose((GLFWwindow*)m_windows.at(winId));
	}
	else return false;
}


bool WindowsManager::SetWindowTitle(size_t winId, std::string const& title) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		glfwSetWindowTitle((GLFWwindow*)m_windows.at(winId), title.c_str());
		return true;
	}
	else return false;
}

bool WindowsManager::SetWindowFullscreen(size_t winId, bool, uint8_t screenId) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		CC_LOG_ERROR("SetWindowFullscreen is not implemented yet.");
		return true;
	}
	else return false;
}

bool WindowsManager::SetWindowSize(size_t winId, uint32_t w, uint32_t h) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		glfwSetWindowSize((GLFWwindow*)m_windows.at(winId), w, h);
		return true;
	}
	else return false;
}

bool WindowsManager::CenterWindow(uint32_t winId, uint8_t screenId) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		int monitorsCount;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorsCount);
		if (screenId > (static_cast<uint32_t>(monitorsCount) - 1))
		{
			CC_LOG_ERROR("Only found {} screens, cannot center window on screen #{}\n", monitorsCount, screenId);
			return false;
		}

		GLFWwindow* window = (GLFWwindow*)m_windows.at(winId);

		int mx, my, mw, mh;
		glfwGetMonitorWorkarea(monitor, &mx, &my, &mw, &mh);

		int ww, wh;
		glfwGetWindowSize(window, &ww, &wh);
		glfwSetWindowPos(window, static_cast<int>((mw - ww) * 0.5), static_cast<int>((mh - wh) * 0.5));
		return true;
	}
	else return false;
}

bool WindowsManager::SetWindowTopLeftCorner(size_t winId, uint32_t x, uint32_t y, uint8_t screenId) const
{
	if (winId < m_windows.size() && m_windows.at(winId) != nullptr)
	{
		GLFWwindow* window = (GLFWwindow*)m_windows.at(winId);
		glfwSetWindowPos(window, x, y);
		return true;
	}
	else return false;
}

void* WindowsManager::GetProcAddress()
{
	return (void*)glfwGetProcAddress;
}