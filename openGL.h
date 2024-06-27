#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_OPENGL_H
#define PixelForge_OPENGL_H

#include "config/config.h"

#if defined(PixelForge_OS_Windows)

#ifdef _MSC_VER

#ifndef PixelForge_LEAN_AND_MEAN
#define PixelForge_LEAN_AND_MEAN
#endif // PixelForge_LEAN_AND_MEAN

#endif // _MSC_VER

#ifndef UNICODE
#define UNICODE
#endif // UNICODE

#include <wtypes.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#elif defined(PixelForge_OS_MacOS)

#include <Cocoa/Cocoa.h>
#include <OpenGL/gl3.h>

#elif defined(PixelForge_OS_Linux)

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>

#endif // defined(PixelForge_OS_Windows)

#endif // PixelForge_OPENGL_H