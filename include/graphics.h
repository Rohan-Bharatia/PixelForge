#pragma once

#include <windows.h>
#include "COM.cpp"

class graphics
{
public:
    #ifndef PIXELFORGE_2D

    struct vec2
    {
        float x;
        float y;
    }

    void triangle(vec2 a, vec2 b, vec2 c, Color col);

    #endif
}