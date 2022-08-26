#pragma once

#include <vector>
#include <string>
#include <stdint.h>

#include "Lib.hpp"

struct WindowsManager {
	WindowsManager();
	~WindowsManager();

	DLLEXPORT static void* GetProcAddress();

	DLLEXPORT operator bool();

	DLLEXPORT bool Initialize();

	DLLEXPORT void* const NewWindow();
	DLLEXPORT void* const NewWindow(uint32_t const width, uint32_t const height);
	DLLEXPORT void* const NewWindow(uint32_t const width, uint32_t const height, std::string const & title);

	DLLEXPORT size_t NumWindows() const;

	DLLEXPORT bool SwapBuffers(size_t winId = 0) const;
	DLLEXPORT bool MakeWindowCurrent(size_t winId = 0) const;

	DLLEXPORT void ProcessEvents();

	DLLEXPORT bool SetWindowTitle(size_t winId, std::string const&) const;

	DLLEXPORT bool SetWindowSize(size_t winId, uint32_t w, uint32_t h) const;
	DLLEXPORT bool SetWindowFullscreen(size_t winId, bool, uint8_t screenId = 0) const;

	DLLEXPORT bool CenterWindow(uint32_t winId, uint8_t screenId = 0) const;
	DLLEXPORT bool SetWindowTopLeftCorner(size_t winId, uint32_t x, uint32_t y, uint8_t screenId = 0) const;

	DLLEXPORT bool WindowShouldClose(size_t winId) const;

	bool initialized = false;

private:
	std::vector<void*> m_windows;
	bool m_gladInitialized = false;
};
