#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_WINDOW_CPP
#define PixelForge_WINDOW_CPP

#include "include/window.hpp"
#include "config/openGL.h"

#if defined(PixelForge_OS_Windows)

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    switch(msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, w_param, l_param);
}

namespace pf
{
    Window::Window(int width, int height, const wchar_t* name, Color col) : m_hinstance(GetModuleHandle(nullptr)), m_width(width), m_height(height),
                                                                            m_name(name)
    {
        WNDCLASS wc;
        wc.lpszClassName = name;
        wc.hInstance     = m_hinstance;
        wc.hIcon         = LoadIcon(nullptr, IDI_WINLOGO);
        wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
        wc.lpfnWndProc   = wnd_proc;

        RegisterClass(&wc);

        DWORD style = WS_CAPTION     |\
                      WS_MINIMIZEBOX |\
                      WS_SYSMENU;

        RECT rc;
        rc.left   = 250;
        rc.top    = 250;
        rc.right  = rc.left + width;
        rc.bottom = rc.top + height;

        AdjustWindowRect(&rc, style, false);

        m_hwnd = CreateWindowEx(0, name, name, style, rc.left, rc.top, width, height, NULL, NULL, m_hinstance, NULL);

        glClearColor(col.r, col.g, col.b, col.a);
        glClear(GL_COLOR_BUFFER_BIT);
        SwapBuffers(GetDC(m_hwnd));

        ShowWindow(m_hwnd, SW_SHOW);

        init_openGL();
    }

    Window::~Window()
    {
        UnregisterClass(m_name, m_hinstance);
    }

    bool Window::process_message()
    {
        MSG msg = {};

        while(PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
                return false;
            
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return true;
    }

    void Window::init_openGL()
    {
        PIXELFORMATDESCRIPTOR pfd =
        { 
            sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
            1,                              // version number
            PFD_DRAW_TO_WINDOW |            // support window
            PFD_SUPPORT_OPENGL |            // support OpenGL
            PFD_DOUBLEBUFFER,               // double buffered
            PFD_TYPE_RGBA,                  // RGBA type
            24,                             // 24-bit color depth
            0, 0, 0, 0, 0, 0,               // color bits ignored
            0,                              // no alpha buffer
            0,                              // shift bit ignored
            0,                              // no accumulation buffer
            0, 0, 0, 0,                     // accum bits ignored
            32,                             // 32-bit z-buffer
            0,                              // no stencil buffer
            0,                              // no auxiliary buffer
            PFD_MAIN_PLANE,                 // main layer
            0,                              // reserved
            0, 0, 0                         // layer masks ignored
        };

        HDC hdc = GetDC(m_hwnd);
        int pixel_format = ChoosePixelFormat(hdc, &pfd);
        SetPixelFormat(hdc, pixel_format, &pfd);

        HGLRC hglrc = wglCreateContext(hdc);
        wglMakeCurrent(hdc, hglrc);
    }
} // namespace pf

#elif defined(PixelForge_OS_MacOS)

namespace pf
{
    @interface AppDelegate : NSObject <NSApplicationDelegate>
    @end

    @implementation AppDelegate
    - static_cast<BOOL>(application_should_terminate_after_last_window_closed: static_cast<NSApplication*>(sender))
    {
        return YES;
    }
    @end
    
    Window(int width, int height, const wchar_t* name, Color col) : m_width(width), m_height(height), m_name(name)
    {
        [NSApplication shared_app];
        m_app = [NSApplication shared_app];
        
        AppDelegate* app_delegate = [[AppDelegate alloc] init];
        [m_app setDelegate:app_delegate];

        NSUInteger style = NSWindowStyleMaskTitled         |\
                           NSWindowStyleMaskClosable       |\
                           NSWindowStyleMaskMiniaturizable |\
                           NSWindowStyleMaskResizable;

        NSRect rect = NSMakeRect(0, 0, width, height);
        m_wnd       = [[NSWindow alloc] initWithContentRect:rect
                                              styleMask:style
                                                  backing:NSBackingStoreBuffered
                                                      defer:NO];
        
        glClearColor(col.r, col.g, col.b, col.a);
        glClear(GL_COLOR_BUFFER_BIT);
        [[m_wnd, openGLContext] flushBuffer]

        [m_wnd setTitle:[NSString stringWithUTF8String:name]];
        [m_wnd makeKeyAndOrderFront:nil];

        init_openGL();
    }

    ~Window()
    {
        [m_wnd close];
    }

    bool process_message()
    {
        NSEvent* event = [m_app nextEventMatchingMask:NSEventMaskAny
                                            untilDate:[NSDate distantPast]
                                               inMode:NSDefaultRunLoopMode
                                              dequeue:YES];

        if(event)
        {
            [m_app sendEvent:event];
            [m_app updateWindows];
        }

        return ![m_app isRunning];
    }

    void Window::init_openGL()
    {
        NSOpenGLPixelFormatAttribute attributes[] =
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAColorSize, 24,
            NSOpenGLPFAAlphaSize, 8,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAAccelerated,
            0
        };
        NSOpenGLPixelFormat *pixel_format = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
        NSOpenGLContext *context          = [[NSOpenGLContext alloc] initWithFormat:pixel_format shareContext:nil];
        [context makeCurrentContext];
        [m_wnd setOpenGLContext:context];
    }
} // namespace pf

#elif defined(PixelForge_OS_Linux)

namespace pf
{
    Window::Window(int width, int height, const wchar_t* name, Color col) : m_width(width), m_height(height),
                                                                            m_name(name)
    {
        m_display = XOpenDisplay(nullptr);

        if(m_display == nullptr)
            throw std::runtime_error("Cannot open display!");

        int screen = DefaultScreen(m_display);
        m_wnd      = XCreateSimpleWindow(m_display, RootWindow(m_display, screen), 10, 10, width, height, 1,
                                         BlackPixel(m_display, screen), WhitePixel(m_display, screen));
        
        glClearColor(col.r, col.g, col.b, col.a);
        glClear(GL_COLOR_BUFFER_BIT);
        glXSwapBuffers(m_display, m_wnd);

        XSetStandardProperties(m_display, m_wnd, name, name, None, nullptr, 0, nullptr);
        XSelectInput(m_display, m_wnd, ExposureMask | KeyPressMask | StructureNotifyMask);

        m_delete_msg = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_display, m_wnd, &m_delete_msg, 1);

        XMapWindow(m_display, m_wnd);

        init_openGL();
    }
    
    Window::~Window()
    {
        XDestroyWindow(m_display, m_wnd);
        XCloseDisplay(m_display);
    }

    bool Window::process_message()
    {
        XEvent event;
        while (XPending(m_display) > 0)
        {
            XNextEvent(m_display, &event);
            if (event.type == ClientMessage && static_cast<Atom>(event.xclient.data.l[0]) == m_delete_msg)
                return false;
        }
        return true;
    }

    void Window::init_openGL()
    {
        GLint attributes[] = 
        {
            GLX_RGBA,
            GLX_DEPTH_SIZE,
            24,
            GLX_DOUBLEBUFFER,
            None
        };

        XVisualInfo *vi = glXChooseVisual(m_display, 0, attributes);
        GLXContext glc  = glXCreateContext(m_display, vi, NULL, GL_TRUE);
        
        glXMakeCurrent(m_display, m_wnd, glc);
    }
} // namespace pf

#endif // PixelForge_OS_Windows

#endif // PixelForge_WINDOW_CPP