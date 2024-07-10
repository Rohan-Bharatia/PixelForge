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

#ifndef _PixelForge_OPENGL_h_
#define _PixelForge_OPENGL_h_

#include "include/os.h"

#ifdef PF_OS_Windows


#ifdef _MSC_VER

#define WIN32_LEAN_AND_MEAN

#endif // _MSC_VER

#include <windows.h>

// OpenGL
#include <GL/gl.h>

#elif PF_OS_Linux || PF_OS_FreeBDS || PF_OS_OpenBDS || PF_OS_NetBDS

// OpenGL
#include <GL/gl.h>

#elif PF_OS_MacOS

// OpenGL
#include <OpenGL/gl.h>

#elif PF_OS_IOS

// OpenGL
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

#elif PF_OS_Android

// OpenGL
#include <OpenGLES/gl.h>
#include <OpenGLES/glext.h>

// OpenGL 2 sRGB extentions
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

#endif // PF_OS_Windows

#endif // _PixelForge_OPENGL_h_