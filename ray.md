# Ray Class
## Overview
The ```Ray<T>``` class is designed to create rays with a vector size of ```T```

--------------------------------------------------------------------

## ```Ray<T>```
create a ray
```cpp
Ray(Vec<T>& origin, Vec<T>& direction);
```

### Parameters
 * ```origin```: The origin of the ray
 * ```direction```: The direction of the ray

### Implementation
```cpp
pf::Ray<5> ray(pf::Vec<5>(0f, 1f, 2f, 3f, 4f), pf::Vec<5>(0f, 1f, 2f, 3f, 4f));
```

--------------------------------------------------------------------

## ```point_at_parameter```
Get an index along a ray
```cpp
Vec<T> point_at_parameter(float p) const;
```

### Parameters
 * ```p```: The index on the ray;

### Implementation
```cpp
#include <iostream>

pf::Ray<5> ray(pf::Vec<5>(0f, 1f, 2f, 3f, 4f), pf::Vec<5>(0f, 1f, 2f, 3f, 4f));

std::cout << ray.point_at_parameter(10) << std::endl;
```

--------------------------------------------------------------------

# Preset Rays
## ```Ray2```
Create a 2d ray
```cpp
Ray2(Vec2 origin, Vec2 direction);
```

### Parameters
 * ```origin```: The origin of the ray
 * ```direction```: The direction of the ray

### Implementation
```cpp
pf::Ray2 ray(pf::Vec2(0, 0), pf::Vec2(3, 2));
```

--------------------------------------------------------------------

## ```Ray3```
Create a 3d ray
```cpp
Ray3(Vec3 origin, Vec3 direction);
```

### Parameters
 * ```origin```: The origin of the ray
 * ```direction```: The direction of the ray

### Implementation
```cpp
pf::Ray3 ray(pf::Vec3(0, 0, 0), pf::Vec3(3, 2, 1));
```

--------------------------------------------------------------------

## ```Ray4```
Create a 4d ray
```cpp
Ray4(Vec4 origin, Vec4 direction);
```

### Parameters
 * ```origin```: The origin of the ray
 * ```direction```: The direction of the ray

### Implementation
```cpp
pf::Ray4 ray(pf::Vec4(0, 0, 0, 0), pf::Vec4(3, 2, 1, 0));
```

--------------------------------------------------------------------

## Full Implementation
```cpp
#include <iostream>

int main(int argc, char* argv[])
{
    pf::Ray2 r2(Vec2(0f, 0f), Vec2(3f, 2f));
    pf::Ray3 r3(Vec3(0f, 0f, 0f), Vec3(3f, 2f, 1f));
    pf::Ray4 r4(Vec4(0f, 0f, 0f, 0f), Vec4(3f, 2f, 1f, 0f));
    pf::Ray<5> r5(Vec<5>(0f, 1f, 2f, 3f, 4f), Vec<5>(0f, 1f, 2f, 3f, 4f));
    
    std::cout << r2.point_at_parameter(10) + r5.point_at_parameter(45) << std::endl;

    return 0;
}
```