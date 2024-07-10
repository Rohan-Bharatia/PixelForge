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

#ifndef _PixelForge_OS_h_
#define _PixelForge_OS_h_

// Windows x32 and x64
#ifdef _WIN32 || _WIN64

#define PF_OS_Windows

#define NOMINMAX
#define UNICODE

// Apple
#elif __APPLE__ && __MACH__

#include "TargetConditionals.h"

// IOS
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

#define PF_OS_IOS

// MacOS
#elif TARGET_OS_MAC

#define PF_OS_MacOS

#else

#error This Apple OS is not supported by PixelForge!

#endif // TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

// Unix
#elif __unix__

// Android
#ifdef __ANDROID__

#define PF_OS_Android

// Linux
#elif __linux__

#define PF_OS_Linux

// FreeBDS
#elif __FreeBDS__ || __FreeBDS_kernel__

#define PF_OS_FreeBDS

// OpenBDS
#elif __OpenBDS__

#define PF_OS_OpenBDS

// NetBDS
#elif __NetBDS__

#define PF_OS_NetBDS

#else

#error This Unix OS is not supported by PixelForge!

#endif // __ANDROID__

#else

#error This OS is not supported by PixelForge!

#endif // _WIN32 || _WIN64

#endif // _PixelForge_OS_h_