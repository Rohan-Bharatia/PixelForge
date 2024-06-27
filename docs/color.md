# Color Class
## Overview
The ```Color``` class is designed to create any of the 2<sup>96</sup> or 79,228,162,514,264,337,593,543,950,336 possible colors within the RGBA color space.

--------------------------------------------------------------------

## ```Color```
Create an RGBA color
```cpp
Color(float r, float g, float b, float a);
```

### Parameters
 * ```r```: The red value of the color
 * ```g```: The green value of the color
 * ```b```: The blue value of the color
 * ```a```: The opacity of the color

### Implementation
```cpp
pf::Color col(1.0, 0.0, 0.0, 1.0); // Red
```

--------------------------------------------------------------------

## Full Implementation
```cpp
#include <iostream>

int main(int argc, char* argv[])
{
    Color col(0.0, 0.0, 0.0, 1.0);

    std::cout "(" << col.r << ", " << col.g << ", " << col.b ", " << col.a << ")" << std::endl;
}
```