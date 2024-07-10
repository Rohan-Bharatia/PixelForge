#pragma region LICENSE

//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
// 
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
// 
//                             ...
// 
//             Copyright (c) Rohan Bharatia 2024

#pragma endregion LICENSE

#pragma once

#ifndef _PixelForge_MACROS_h_
#define _PixelForge_MACROS_h_

#include "include/os.h"

// Debug macro
#ifdef !NDEBUG

#define PF_DEBUG

#endif

#ifdef PF_OS_Windows

// Import/Export macros
#define PF_API_EXPORT __declspec(dllexport)
#define PF_API_IMPORT __declspec(dllimport)

#define PF_DISCRETE_GPU                                                                         \
    extern "C" __declspec(dllexport) unsigned long NvidiaOptimus_enablement                = 1; \
    extern "C" __declspec(dllexport) unsigned long AmdPowerXpress_request_high_preformance = 1;

#ifdef _MSC_VER

#pragma warning(disable : 4251)

#endif // _MSC_VER

#else

// Import/Export macros
#define PF_API_EXPORT __attribute__((__visibility__("default")))
#define PF_API_IMPORT __attribute__((__visibility__("default")))

#define PF_DISCRETE_GPU

#endif // PF_OS_Windows

#endif // _PixelForge_MACROS_h_