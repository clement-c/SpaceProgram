#include <thread>
#include <chrono>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Engine/Core/Application.hpp"
#include "Engine/Core/Logging.hpp"
#include "Engine/Core/Window.hpp"

namespace fs = std::filesystem;
using namespace std::chrono_literals;

Application::Application(int argc, char **argv) : m_windowsManager{}, m_loop{}
{
	for (int i = 0; i < argc; i++)
		m_args.emplace_back(argv[i]);

	// IF UI

	if (!m_windowsManager.Initialize())
	{
		CC_LOG_ERROR("Could not initialize the windows manager, exiting.");
		return;
	}
}

std::filesystem::path Application::GetPath() const
{
	return fs::path(m_args[0]);
}

bool Application::SetLoop(LoopType loop)
{
	m_loop = loop;
	return true;
}

int Application::Run()
{
	int status = 0;

	auto start_time = std::chrono::high_resolution_clock::now();
	auto now = start_time;

	auto time_since_start = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start_time);

	std::chrono::duration<double, std::nano> loop_duration{0.0};
	std::chrono::duration<double, std::nano> target_duration(1.0f / 60.0f);

	// Renderer renderer;
	while (!ShouldExit())
	{
		// Match target fps
		std::this_thread::sleep_for(target_duration - loop_duration);

		// Update time for start of loop
		now = std::chrono::high_resolution_clock::now();
		time_since_start = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start_time);

		// Processing events
		m_windowsManager.ProcessEvents();

		// Run gameplay loop
		if (m_loop)
			status = m_loop(*this, std::chrono::duration_cast<std::chrono::duration<double>>(time_since_start).count());
		if (status != 0)
			break;

		// Render windows
		for (auto win_id = 0; win_id < m_windowsManager.GetNumWindows(); win_id++)
		{
			auto *window = m_windowsManager.GetWindow(win_id);
			if (window)
			{
				m_windowsManager.MakeWindowCurrent(win_id);
				// Render
				window->GetRenderer().RenderAll();
				m_windowsManager.SwapBuffers(win_id);
			}
		}

		// Systems
		loop_duration = std::chrono::high_resolution_clock::now() - now;
	}
	return status;
}

inline bool Application::ShouldExit()
{
	bool allWindowsClosed = true;
	for (auto i = 0; i < GetWindowsManager().GetNumWindows(); i++)
		allWindowsClosed = allWindowsClosed && (m_windowsManager.WindowShouldClose(i));
	if (allWindowsClosed)
		m_shouldExit = true;
	else
		m_shouldExit = m_shouldExit;
	return m_shouldExit;
}

bool Application::Exit(int code)
{
	bool allWindowsClosed = true;
	for (auto i = 0; i < GetWindowsManager().GetNumWindows(); i++)
		allWindowsClosed = allWindowsClosed && (m_windowsManager.CloseWindow(i));
	m_shouldExit |= allWindowsClosed;
	return allWindowsClosed;
}

Window *const Application::NewWindow()
{
	return m_windowsManager.NewWindow();
}

Window *const Application::NewWindow(uint32_t const w, uint32_t const h)
{
	return m_windowsManager.NewWindow(w, h);
}

Window *const Application::NewWindow(uint32_t const w, uint32_t const h, std::string const &title)
{
	return m_windowsManager.NewWindow(w, h, title);
}

WindowsManager &Application::GetWindowsManager()
{
	return m_windowsManager;
}

Engine &Application::GetEngine()
{
	return m_engine;
}
