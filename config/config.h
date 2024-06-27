#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_CONFIG_H
#define PixelForge_CONFIG_H

#if defined(_WIN32) || defined(_WIN64)

#define PixelForge_OS_Windows

#elif defined(__APPLE__) && defined(__MACH__) && TARGET_OS_MAC

#include <TargetConditionals.h>

#define PixelForge_OS_MacOS

#elif defined(__unix__) && defined(__linux__)

#define PixelForge_OS_Linux

#else

#error This OS is not supported by PixelForge!

#endif // defined(_WIN32) || defined(_WIN64)

#endif // PixelForge_CONFIG_H