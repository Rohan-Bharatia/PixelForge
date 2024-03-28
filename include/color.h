#pragma once

class color
{
public:
    struct Color
    {
        float red;
        float green;
        float blue;
    }

    Color rgba(int r, int g, int b, float a);
}