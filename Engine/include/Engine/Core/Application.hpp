#pragma once
#include <functional>
#include <string>
#include <vector>

#include "Lib.hpp"
#include "WindowsManager.hpp"
#include "../Engine.hpp"

class Engine;

class Application
{
public:
	using LoopType = std::function<int(Application&, double)>;

	DLLEXPORT Application();
	DLLEXPORT ~Application() = default;

	/**
	 * @brief Set the main loop for the application
	 * 
	 * @return bool
	 */
	DLLEXPORT bool SetLoop(LoopType);

	DLLEXPORT uint32_t const NewWindow();
	DLLEXPORT uint32_t const NewWindow(uint32_t const width, uint32_t const height);
	DLLEXPORT uint32_t const NewWindow(uint32_t const width, uint32_t const height, std::string const& title);

	DLLEXPORT WindowsManager& GetWindowsManager();

	DLLEXPORT bool InitializeEngine();
	DLLEXPORT Engine& GetEngine();

	DLLEXPORT int Run();

protected:
	inline bool ShouldExit();

	WindowsManager m_windowsManager;
	LoopType m_loop;
	Engine m_engine;
};
