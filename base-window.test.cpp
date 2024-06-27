#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_WINDOW_TEST_CPP
#define PixelForge_WINDOW_TEST_CPP

// std
#include <iostream>
#include <array>

#include "pf1.h"

int main(int argc, char* argv[])
{
    std::cout << "Creating Window..." << std::endl;
    
    pf::Color bkgnd(0.1f, 0.2f, 0.3f, 1.0f);
    pf::Window* window = new pf::Window(640, 480, L"PixelForge Test Application", bkgnd);

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

#endif // PixelForge_WINDOW_TEST_CPP