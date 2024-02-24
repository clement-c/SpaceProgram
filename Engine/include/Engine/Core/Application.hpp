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
	using LoopType = std::function<bool(Application &, double)>;

	DLLEXPORT Application() = delete;
	DLLEXPORT Application(int argc, char **argv);
	DLLEXPORT ~Application() = default;

	DLLEXPORT std::filesystem::path GetPath() const;

	/**
	 * @brief Set the main loop for the application
	 *
	 * @return bool
	 */
	DLLEXPORT bool SetLoop(LoopType);

	DLLEXPORT Window *const NewWindow();
	DLLEXPORT Window *const NewWindow(uint32_t const width, uint32_t const height);
	DLLEXPORT Window *const NewWindow(uint32_t const width, uint32_t const height, std::string const &title);

	DLLEXPORT WindowsManager &GetWindowsManager();

	DLLEXPORT Engine &GetEngine();

	DLLEXPORT int Run();

	DLLEXPORT bool Exit(int = 0);

protected:
	inline bool ShouldExit();

private:
	std::vector<std::string> m_args;

	WindowsManager m_windowsManager;
	Engine m_engine;
	LoopType m_loop;

	bool m_shouldExit = false;
};
