#include "include/window.h"
#include <window.h>
#include <d2d1.h>

// Basic functions
void WINAPI window::Window(uint32_t width, uint32_t height, wchar_t name[], Color col)
{
    m_width = width;
    m_height = height;
    m_col = col;
    
    open = true;
    close = false;

    WNDCLASS wc = {};
    wc.lpfnWndProc = win_proc;
    wc.hInstance = instance;
    wc.lpszClassName = name;

    registerClass(&wc);

    // state_info *state;
    // if(state == NULL)
    //     return;

    HWND hwnd = CreateWindowEx(0, name, L"PixelForge Application", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL,
                               m_instance, NULL);
    
    if(hwnd == NULL)
        return;

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
    case WM_CREATE:
        if(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory))
        {
            return;
        }

        return;

    case WM_DESTROY:
        close = true;
        open = false;
        
        PostQuitMessage(0);
        return;
    
    case WM_PAINT:
        HRESULT hr2;
        PAINTSTRUCT ps;

        if(SUCCEEDED(hr))
        {    
            BeginPaint(m_hwnd, &ps);

            render_target -> BeginPaint();
            render_target -> Clear(ColorF(TRANSPARENT));
            render_target -> FillTriangle(tri, brush);
            hr2 = render_target -> EndDraw();

            if(FAILED(hr2) || hr == D2DERR_RECREATE_TARGET)
            {
                safe_release(&render_target);
                safe_release(&brush);
            }

            EndPaint(m_hwnd, &ps);
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
