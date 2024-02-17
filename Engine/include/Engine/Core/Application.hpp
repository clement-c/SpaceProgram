#pragma once
#include <filesystem>
#include <functional>
#include <string>
#include <vector>

#include "Engine/Engine.hpp"
#include "Engine/Core/Lib.hpp"
#include "Engine/Core/WindowsManager.hpp"

class Application
{
public:
	using LoopType = std::function<int(Application&, double)>;

	DLLEXPORT Application() = delete;
	DLLEXPORT Application(int argc, char** argv);
	DLLEXPORT ~Application() = default;

	DLLEXPORT std::filesystem::path GetPath() const;

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

	DLLEXPORT Engine& GetEngine();

	DLLEXPORT int Run();

	DLLEXPORT bool Exit(int = 0);

protected:
	inline bool ShouldExit();

private:
	std::vector<std::string> m_args;

	WindowsManager m_windowsManager;
	LoopType m_loop;
	Engine m_engine;
};
