#pragma once

#include "graphics.h"

class transform : public graphics : private graphics
{
public:
    void rotate(vec2 a);
    void scale(float weight);
    void translate(bool axis, float weight);
    void skew(bool axis, float weight);
}