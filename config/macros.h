#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_MACROS_H
#define PixelForge_MACROS_H

#include "config/config.h"

#if defined(NDEBUG)

#define PixelForge_DEBUG

#endif // defined(NDEBUG)

#if defined(PixelForge_OS_Windows)

// Discrete GPU macro
#define PixelForge_DISCRETE_GPU_PREFERENCE                                                      \
    extern "C" __declspec(dllexport) unsigned long NvidiaOptimus_enablement = 1;                \
    extern "C" __declspec(dllexport) unsigned long AMDPowerXpress_request_high_preformance = 1;

// Import/export macros
#define PixelForge_API_EXPORT __declspec(dllexport)
#define PixelForge_API_IMPORT __declspec(dllimport)

#else

// Discrete GPU macro
#define PixelForge_DISCRETE_GPU_PREFERENCE

// Import/export macros
#define PixelForge_API_EXPORT __attribute__((__visibility("default")))
#define PixelForge_API_IMPORT __attribute__((__visibility("default")))

#endif // defined(PixelForge_OS_Windows)

#endif // PixelForge_MACROS_H