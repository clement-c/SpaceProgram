#pragma once

#include <string>

#include <fmt/core.h>
#include <fmt/color.h>

#define CC_NO_LOG          0x00
#define CC_ERROR_LEVEL     0x01
#define CC_WARNING_LEVEL   0x02
#define CC_SUCCESS_LEVEL   0x03
#define CC_INFO_LEVEL      0x04
#define CC_DEBUG_LEVEL     0x05

#ifndef CC_LOG_LEVEL
#ifndef NDEBUG
#define CC_LOG_LEVEL CC_DEBUG_LEVEL
#else
#define CC_LOG_LEVEL CC_INFO_LEVEL
#endif
#endif

#if CC_LOG_LEVEL >= CC_DEBUG_LEVEL
#define CC_LOG_DEBUG(...) fmt::print(fg(fmt::color::cyan), __VA_ARGS__)
#else
#define CC_LOG_DEBUG(...)
#endif

#if CC_LOG_LEVEL >= CC_INFO_LEVEL
#define CC_LOG_INFO(...) fmt::print(fmt::emphasis::bold, __VA_ARGS__)
#else
#define CC_LOG_INFO(...)
#endif

#if CC_LOG_LEVEL >= CC_SUCCESS_LEVEL
#define CC_LOG_SUCCESS(...) fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, __VA_ARGS__)
#else
#define CC_LOG_SUCCESS(...)
#endif

#if CC_LOG_LEVEL >= CC_WARNING_LEVEL
#define CC_LOG_WARNING(...) fmt::print(fg(fmt::color::orange) | fmt::emphasis::bold, __VA_ARGS__)
#else
#define CC_LOG_WARNING(...)
#endif

#if CC_LOG_LEVEL >= CC_ERROR_LEVEL
#define CC_LOG_ERROR(...) fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, __VA_ARGS__)
#else
#define CC_LOG_ERROR(...)
#endif
