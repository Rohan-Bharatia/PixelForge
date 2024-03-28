#include "transformations.h"
#include "pf1.h"
#include <windows.h>
#include <D2D1.h>
using namespace D2D1;

void transform::rotate(vec2 a, float weight)
{
    #ifdef ANGLE_MODE_DEGREES
    render_target -> SetTransform(Matrix3x2F::Rotation(weight, Point2F(a.x, a.y)));
    render_target -> SetTransform(Matrix3x2F::Identity());
}

void transform::scale(vec2 a, float weight)
{
    render_target -> SetTransform(Matrix3x2F::Scale(weight, Point2F(a.x, a.y)));
    render_target -> SetTransform(Matrix3x2F::Identity());
}

void transform::translate(bool axis, float weight)
{
    if(axis == true)
    {
        render_target -> SetTransform(Matrix3x2F::Translate(weight, 0));
    }
    if (axis == false)
    {
        render_target -> SetTransform(Matrix3x2F::Translate(0, weight));
    }
    
    render_target -> SetTransform(Matrix3x2F::Identity());
}

void transform::skew(bool axis, vec2 a, float weight)
{
    if(axis == true)
    {
        render_target -> SetTransform(Matrix3x2F::Skew(weight, 0, Point2F(a.x, a.y)));
    }
    if(axis == false)
    {
        render_target -> SetTransform(Matrix3x2F::Skew(0, weight, Point2F(a.x, a.y)));
    }

    render_target -> SetTransform(Matrix3x2F::Identity());
}