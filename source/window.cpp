#ifndef UNICODE
#define UNICODE
#endif

#include "include/window.h"
#include <window.h>

// Basic functions
void WINAPI window::Window(uint32_t width, uint32_t height, wchar_t name[], float color, uint32_t fps = 120)
{
    m_width = width;
    m_height = height;
    m_color = color;
    
    // Brodcasting 'on_open()'
    open = true;
    close = false;

    // Register window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = win_proc;
    wc.hInstance = instance;
    wc.lpszClassName = name;

    registerClass(&wc);

    // state_info *state;
    // if(state == NULL)
    //     return;

    // Creating window
    HWND hwnd = CreateWindowEx(0, name, L"PixelForge Application", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL,
                               m_instance, NULL);
    
    if(hwnd == NULL)
        return;

    // Displaying window
    ShowWindow(hwnd, show);

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return;
}

LRESULT CALLBACK window::win_proc(HWND hwnd, uint msg, WPARAM w_param, LPARAM l_param)
{
    state_info *state;
    if(msg == WM_CREATE)
    {
        CREATESTRUCT *create = reinterpret_cast<CREATESTRUCT*>(l_param);
        state = reinterpret_cast<state_info*>(create -> lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)state);
    }
    else
    {
        state = app_state(hwnd);
    }

    switch(msg)
    {
    case WM_DESTROY:
        // Brodcasting 'on_close()'
        close = true;
        open = false;
        
        PostQuitMessage(0);
        return;
    
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, (HBRUSH), (COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }

        return;
    }

    return DefWindowProc(hwnd, msg, w_param, l_param);
}

inline state_info window::app_state(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    state_info *m_state = reinterpret_cast<state_info*>(ptr);

    return m_state;
}

// Events
bool window::on_open()
{
    return open;
}
bool window::on_close()
{
    return close;
}
