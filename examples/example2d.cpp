#define PIXELFORGE_2D
#include <PixelForge/pf1.h>
using namespace PixelForge;

int main()
{
    Window window(640, 480, L"2D Graphics Example");

    vec2 a1 = vec2(0, HEIGHT);
    vec2 b1 = vec2(WIDTH / 2, 0);
    vec2 c1 = vec2(WIDTH, HEIGHT);
    color col1 = color(255, 255, 255, 1.0);

    Draw::triangle(a1, b1, c1, col1);

    return 0;
}