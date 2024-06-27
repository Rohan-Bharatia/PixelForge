# Vector Class
## Overview
The ```Vec<T>``` class is designed to create vectors with a size of ```T```

--------------------------------------------------------------------

## ```Vec<T>```
Create a vector
```cpp
Vec(std::array<float, T> data);
```

### Parameters
 * ```data```: The data inputed into the class

### Implementation
```cpp
pf::Vec<5> vector(0f, 0f, 0f, 0f, 0f);
```

--------------------------------------------------------------------

## ```value```
Return a value of the vector
```cpp
float value(size_t idx);
```

### Parameters
 * ```idx```: The index of the vector that is being returned

### Implementation
```cpp
#include <iostream>

pf::Vec<5> vector(1f, 2f, 3f, 4f, 5f);

std::cout << vector.value(2); // 3rd index
```

--------------------------------------------------------------------

# Preset Vectors
## ```Vec2```
Create a 2d vector
```cpp
Vec2(float x, float y);
```

### Parameters
 * ```x```: The X position of the vector
 * ```y```: The Y position of the vector

### Implementation
```cpp
pf::Vec2 vector(1f, 2f);
```

--------------------------------------------------------------------

## ```Vec3```
Create a 3d vector
```cpp
pf::Vec2(float x, float y, float z);
```

### Parameters
 * ```x```: The X position of the vector
 * ```y```: The Y position of the vector
 * ```z```: The z position of the vector

### Implementation
```cpp
pf::Vec3 vector(1f, 2f, 3f);
```

--------------------------------------------------------------------

## ```Vec4```
Create a 4d vector
```cpp
Vec2(float x, float y, float z, float w);
```

### Parameters
 * ```x```: The X position of the vector
 * ```y```: The Y position of the vector
 * ```z```: The z position of the vector
 * ```w```: The w position of the vector

### Implementation
```cpp
pf::Vec4 vector(1f, 2f, 3f, 4f);
```

--------------------------------------------------------------------

## Full Implementation
```cpp
#include <iostream>

int main(int argc, char* argv[])
{
    pf::Vec2 v2(1f, 2f);
    pf::Vec2 v3(1f, 2f, 3f);
    pf::Vec2 v4(1f, 2f, 3f, 4f);
    pf::Vec<5> v5(1f, 2f, 3f, 4f, 5f);
    
    std::cout << v2.value(0) + v5.value(4) << std::endl;

    return 0;
}
```