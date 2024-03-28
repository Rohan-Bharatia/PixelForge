#define PIXELFORGE_3D
#include <PixelForge/pf1.h>
using namespace PixelForge;
using namespace Color;
using namespace Draw;

int main()
{
    Window window(640, 480, L"3D Graphics Example", rgba(0, 0, 0, 1.0));

    vec3 a = vec3(0, 0, 0);
    vec3 b = vec3(50, 50, 50);
    Color color = rgba(255, 255, 255, 1.0);

    cube(a, b, color);

    return 0;
}