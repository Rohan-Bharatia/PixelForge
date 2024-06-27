# Camera Class
## Overview
The ```camera``` class is designed to create a camera

--------------------------------------------------------------------

## ```Camera```
Create a camera
```cpp
Camera(Window* window, Vec3& position, float* aspect_ratio, float FOV);
```

### Parameters
 * ```window```: The window
 * ```position```: The position of the camera
 * ```aspect_ratio```: The aspect ratio of the camera
 * ```FOV```: The field of view of the camera

### Implementation
```cpp
pf::Window* window = new pf::Window(640, 480, L"PixelForge Test Application", bkgnd);
pf::Camera camera(window, pf::Vec3(0, 0, 0.3), window.width / window.height, 130);
```
--------------------------------------------------------------------

## ```set_aspect_ratio```
Set the aspect ratio
```cpp
void set_aspect_ratio(float* aspect_ratio);
```

### Parameters
 * ```aspect_ratio```: The aspect ratio

### Implementation
```cpp
camera.set_aspect_ratio(1 + 1 / 3);
```
--------------------------------------------------------------------

## ```set_FOV```
Set the field of view
```cpp
void set_FOV(float FOV);
```

### Parameters
 * ```FOV```: The field of view

### Implementation
```cpp
camera.set_FOV(130);
```
--------------------------------------------------------------------

## ```view_matrix```
```cpp
Mat4x4 view_matrix() const;
```

### Implementation
```cpp
pf::Mat4x4 view = camera.view_matrix();
```
--------------------------------------------------------------------

## ```projection_matrix```
```cpp
Mat4x4 projection_matrix() const;
```

### Implementation
```cpp
pf::Mat4x4 project = camera.projection_matrix();
```
--------------------------------------------------------------------

## ```move```
Move the camera to a specified target
```cpp
void move(Vec3& target);
```

### Parameters
 * ```target```: The specified target that the camera will move to

### Implementation
```cpp
camera.move(Vec3(0, 0, 1));
```
--------------------------------------------------------------------

## ```look_at```
Make the camera look at a specified target
```cpp
void look_at(Vec3& target);
```

### Parameters
 * ```target```: The specified target that the camera will look at

### Implementation
```cpp
camera.look_at(Vec3(14, 13, 12));
```
--------------------------------------------------------------------

## ```rotate```
Rotate the camera around specified degrees
```cpp
void rotate(float roll, float yaw, float pitch);
```

### Parameters
 * ```roll```: The rotation on the X-axis (in degrees)
 * ```yaw```: The rotation on the Y-axis (in degrees)
 * ```pitch```: The rotation on the Z-axis (in degrees)

### Implementation
```cpp
camera.rotate(10, 20, 30);
```
--------------------------------------------------------------------

## ```normalize``` (*Private*)
Normalize a vector
```cpp
Vec3 normalize(Vec3& n) const;
```

--------------------------------------------------------------------

## ```cross``` (*Private*)
The cross product of a vector
```cpp
Vec3 cross(Vec3& a, Vec3& b) const;
```

--------------------------------------------------------------------

## ```dot``` (*Private*)
The dot product of a vector
```cpp
float dot(Vec3& a, Vec3& b) const;
```

--------------------------------------------------------------------

## Full Implementation
```cpp
int main(int argc, char* argv[])
{
    pf::Window* window = new pf::Window(640, 480, L"PixelForge Test Application", bkgnd);
    pf::Camera camera(window, pf::Vec3(0, 0, 0.3), window.width / window.height, 130);

    camera.move(Vec3(0, 0, 1));
    camera.look_at(Vec3(14, 13, 12));
    camera.rotate(10, 20, 30);

    std::cout << camera.view_matrix() << std::endl;
    std::cout << camera.projection_matrix() << std::endl;

    return 0;
}
```