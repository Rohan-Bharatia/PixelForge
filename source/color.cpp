#include "include/color.h"
#include <cmath>

Color color::rgba(int r, int g, int b, float a)
{
    float red = (std::round(((1 - a) * 255) + (a * r))) / 255;
    float green = (std::round(((1 - a) * 255) + (a * r))) / 255;
    float blue = (std::round(((1 - a) * 255) + (a * r))) / 255;

    return Color(red, green, blue);
}