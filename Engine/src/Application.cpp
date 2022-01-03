#include <thread>
#include <chrono>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Engine/Core/Application.hpp"
#include "Engine/Core/Logging.hpp"

using namespace std::chrono_literals;



Application::Application() : m_windowsManager{}, m_loop{} {
	if (!m_windowsManager.Initialize())
	{
		CC_LOG_ERROR("Could not initialize the windows manager, exiting.");
	}
}

bool Application::SetLoop(LoopType loop)
{
	m_loop = loop;
	return true;
}

int Application::Run()
{
	if (!m_windowsManager.initialized) return 1;

	int status = 0;
	auto startTime = std::chrono::high_resolution_clock::now();
	auto now = startTime;
	auto prevTime = startTime;

	auto timeSinceStart = std::chrono::duration_cast<std::chrono::nanoseconds>(now - startTime);
	auto loopDuration = now - prevTime;

	std::chrono::duration<double, std::nano> aimDuration(1.0f/60.0f);

	// Renderer renderer;
	while (!ShouldExit())
	{
		// Match target fps
		std::this_thread::sleep_for(aimDuration - loopDuration);

		// Update time for start of loop
		now = std::chrono::high_resolution_clock::now();
		timeSinceStart = std::chrono::duration_cast<std::chrono::nanoseconds>(now - startTime);

		// Processing events
		m_windowsManager.ProcessEvents();

		// Run gameplay loop
		if (m_loop) status = m_loop(*this, std::chrono::duration_cast<std::chrono::duration<double>>(timeSinceStart).count());
		if (status != 0) break;

		// Systems

		loopDuration = std::chrono::high_resolution_clock::now() - now;
	}
	return status;
}

inline bool Application::ShouldExit()
{
	bool allWindowsClosed = true;
	for(auto i = 0; i < GetWindowsManager().NumWindows(); i++)
		allWindowsClosed = allWindowsClosed && (m_windowsManager.WindowShouldClose(i));
	if(allWindowsClosed) return true;
	return false;
}

uint32_t const Application::NewWindow()
{
	m_windowsManager.NewWindow();
	return static_cast<uint32_t>(m_windowsManager.NumWindows() - 1);
}

uint32_t const Application::NewWindow(uint32_t const w, uint32_t const h)
{
	m_windowsManager.NewWindow(w, h);
	return static_cast<uint32_t>(m_windowsManager.NumWindows() - 1);
}

uint32_t const Application::NewWindow(uint32_t const w, uint32_t const h, std::string const& title)
{
	m_windowsManager.NewWindow(w, h, title);
	return static_cast<uint32_t>(m_windowsManager.NumWindows() - 1);
}

WindowsManager& Application::GetWindowsManager() { return m_windowsManager; }
