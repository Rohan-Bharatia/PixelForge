#pragma once

#include <windows.h>

class window()
{
public:
    // Main variables
    uint32_t w = m_width;
    uint32_t h = m_height;

    // Basic functions
    void WINAPI Window(uint32_t width, uint32_t height, wchar_t name[]);

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
    LRESULT CALLBACK win_proc(HWND hwnd, uint msg, WPARAM w_param, LPARAM l_param);
    struct state_info{};
    inline state_info app_state(HWND hwnd);
}
