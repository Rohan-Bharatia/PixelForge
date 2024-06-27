# Window Class
## Overview
The ```Window``` class is designed to open a window on any Windows, MacOS, or Linux operating system.

--------------------------------------------------------------------

## ```Window```
Create a blank window
```cpp
Window(int width, int height, const wchar_t* name, Color col)
```

### Parameters
 * ```width```: The width (x-axis) of the window
 * ```height```: The height (y-axis) of the window
 * ```name```: The name of the window
 * ```col```: The background color of the window

### Implementation
```cpp
pf::Color bkgnd(0.1f, 0.2f, 0.3f, 1.0f);
pf::Window* window = new Window(640, 480, L"PixelForge Test Application", bkgnd);
```

--------------------------------------------------------------------

## ```~window```
Close a window
```cpp
~Window();
```

### Implementation
```cpp
~window();
```

--------------------------------------------------------------------

## ```process_message```
Check if the window has been closed or not
```cpp
bool process_message();
```

### Implementation
```cpp
if(window->process_message())
{
    // Do something
}
```

--------------------------------------------------------------------

## ```init_openGL``` (*Private*)
Initialize OpenGL
```cpp
void init_openGL();
```

--------------------------------------------------------------------

## Full Implementation
```cpp
int main(int argc, char* argv[])
{
    std::cout << "Creating Window..." << std::endl;
    
    pf::Color bkgnd(0.1f, 0.2f, 0.3f, 1.0f);
    pf::Window* window = new Window(640, 480, L"PixelForge Test Application", bkgnd);

    bool running = true;
    while(running)
    {
        if(window->process_message())
        {
            std::cout << "Closing Window..." << std::endl;

            ~window();

            running = false;
        }

        // Render

        Sleep(10);
    }

    delete window;
    return 0;
}
```