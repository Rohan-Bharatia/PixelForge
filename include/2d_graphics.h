#pragma once

#include "window.h"
#include <windows.h>
#include <d2d1.h>

class graphics : private window
{
public:

    struct vec2
    {
        float x;
        float y;
    }

    void triangle(vec2 a, vec2 b, vec2 c, Color col);

private:
    ID2D1Factory factory;
    ID2D1HwndRenderTarget render_target;
    ID2D1SolidColorBrush brush;
    void resize();
}