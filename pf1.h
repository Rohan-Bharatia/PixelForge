#ifndef UNICODE
#define UNICODE
#endif

#include "include/window.h"
#include "include/graphics.h"
#include "include/color.h"
#include "include/transformations.h"
#include "COM.cpp"
#include "DPI.cpp"
using namespace PixelForge;
using namespace Color;
using namespace Draw;

#define WIDTH PixelForge::Window::w;
#define HEIGHT PixelForge::Window::h;

#define X_DIRECTION true
#define Y_DIRECTION true

#define WHITE rgba(255, 255, 255, 1.0)
#define BLACK rgba(0, 0, 0, 1.0)
#define GRAY rgba(128, 128, 128, 1.0)
#define GREY rgba(128, 128, 128, 1.0)
#define TRANSPARENT rgba(0, 0, 0, 0.0)
#define RED rgba(255, 0, 0, 1.0)
#define GREEN rgba(0, 128, 0, 1.0)
#define BLUE rgba(0, 0, 255, 1.0)
#define CYAN rgba(0, 255, 255, 1.0)
#define MAGENTA rgba(255, 0, 255, 1.0)
#define YELLOW rgba(255, 255, 0, 1.0)
#define LIME rgba(0, 255, 0, 1.0)
#define MAROON rgba(128, 0, 0, 1.0)
#define ORANGE rgba(255, 128, 0, 1.0)
#define PURPLE rgba(128, 0, 128, 1.0)

namespace PixelForge
{
    class Window : public window;
    class Graphics : public graphics;
    class Color : public color;
    class Transform : public transform;
}