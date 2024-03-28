#define PIXELFORGE_2D
#include <PixelForge/pf1.h>
using namespace PixelForge;
using namespace Color;
using namespace Draw;

int main()
{
    Window window(640, 480, L"2D Graphics Example", rgba(0, 0, 0, 1.0));

    vec2 a = vec2(0, HEIGHT);
    vec2 b = vec2(WIDTH / 2, 0);
    vec2 c = vec2(WIDTH, HEIGHT);
    Color color = rgba(255, 255, 255, 1.0);

    triangle(a, b, c, color);

    return 0;
}