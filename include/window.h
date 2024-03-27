#pragma once

#include <windows.h>

class Window()
{
public:
    // Main variables
    uint32_t WIDTH = m_width;
    uint32_t HEIGHT = m_height;

    // Basic functions
    void WINAPI Window(uint32_t width, uint32_t height, wchar_t name[], auto color, uint fps = 120);
    void close();
    LRESULT CALLBACK win_proc(HWND hwnd, uint msg, WPARAM w_param, LPARAM l_param);

    // Events
    bool on_open();
    bool on_close();

private:
    // Member variables
    HISNTANCE instance;
    HISNTANCE prev_instance;
    PWSTR line;
    int show;
    uint32_t m_width;
    uint32_t m_height;
    float m_color;
    bool open = false;
    bool close = false;
}
