#pragma once

#include <memory>
#include <tuple>
#include <vector>
#include <string>
#include <stdint.h>

#include "Lib.hpp"

struct Window;

/**
 * @brief Class to manipulate windows in the engine
 *
 */
struct WindowsManager
{
	WindowsManager();
	~WindowsManager();

	// DLLEXPORT static void *GetProcAddress();

	DLLEXPORT operator bool();

	DLLEXPORT bool Initialize();

	/**
	 * @brief Create a new window of default size and name
	 *
	 * @return void* const
	 */
	DLLEXPORT Window *const NewWindow();
	DLLEXPORT Window *const NewWindow(uint32_t const width, uint32_t const height);
	DLLEXPORT Window *const NewWindow(uint32_t const width, uint32_t const height, std::string const &title);

	DLLEXPORT int GetNumMonitors() const;

	/**
	 * @brief Get the number of windows currently used (some might be hidden)
	 *
	 * @return size_t
	 */
	DLLEXPORT size_t GetNumWindows() const;

	DLLEXPORT bool SwapBuffers(size_t winId = 0) const;
	DLLEXPORT bool MakeWindowCurrent(size_t winId = 0) const;

	DLLEXPORT void ProcessEvents();

	DLLEXPORT Window *GetWindow(size_t winId) const;
	/**
	 * @brief Change the title of a window
	 *
	 * @param winId
	 * @return bool
	 */
	DLLEXPORT bool SetWindowTitle(size_t winId, std::string const &) const;

	DLLEXPORT bool SetWindowSize(size_t winId, uint32_t w, uint32_t h) const;
	DLLEXPORT bool SetWindowFullscreen(size_t winId, bool, uint8_t screenId = 0) const;

	DLLEXPORT bool CenterWindow(uint32_t winId, uint8_t screenId = 0) const;
	DLLEXPORT bool SetWindowTopLeftCorner(size_t winId, uint32_t x, uint32_t y, uint8_t screenId = 0) const;

	DLLEXPORT bool CloseWindow(size_t winId) const;
	DLLEXPORT bool WindowShouldClose(size_t winId) const;

	// DLLEXPORT bool GetCurrentWindowSurface

	bool initialized = false;

private:
	std::vector<std::unique_ptr<Window>> m_windows;
	bool m_gladInitialized = false;
};
