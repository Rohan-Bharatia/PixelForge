#ifndef UNICODE
#define UNICODE
#endif

#include "include/window.h"
#include <window.h>

// Basic functions
void WINAPI Window::Window(uint32_t width, uint32_t height, wchar_t name[], uint32_t fps = 120)
{
    m_width = width;
    m_height = height;
    
    // Brodcasting 'on_open()'
    open = true;
    close = false;

    // Register window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = win_proc;
    wc.hInstance = instance;
    wc.lpszClassName = name;

    registerClass(&wc);

    // Creating window
    HWND hwnd = CreateWindowEx(0, name, L"PixelForge Application", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL,
                               m_instance, NULL);
    
    if(hwnd == NULL)
    {
        return;
    }

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

LRESULT CALLBACK Window::win_proc(HWND hwnd, uint msg, WPARAM w_param, LPARAM l_param)
{
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

// Events
bool Window::on_open()
{
    return open;
}
bool Window::on_close()
{
    return close;
}
