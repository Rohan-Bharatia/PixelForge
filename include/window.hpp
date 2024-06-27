#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_WINDOW_HPP
#define PixelForge_WINDOW_HPP

#include "config/openGL.h"
#include "color.h"

#if defined(PixelForge_OS_Windows)

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

namespace pf
{
    class Window
    {
    public:
        Window(int width, int height, const wchar_t* name, Color col);
        ~Window();

        Window(const Window &) = delete;
        Window &operator = (const Window &) = delete;

        bool process_message();

        const int width = m_width;
        const int height = m_height;
        const wchar_t* name = m_name;
    
    private:
        const wchar_t* m_name;
        int m_width;
        int m_height;
        HINSTANCE m_hinstance;
        HWND m_hwnd;

        void init_openGL();
    };
} // namespace pf

#elif defined(PixelForge_OS_MacOS)

namespace pf
{
    class Window
    {
    public:
        Window(int width, int height, const wchar_t* name, Color col);
        ~Window();

        Window(const Window &) = delete;
        Window &operator = (const Window &) = delete;

        bool process_message();

        const int width = m_width;
        const int height = m_height;
        const wchar_t* name = m_name;
    
    private:
        const wchar_t* m_name;
        int m_width;
        int m_height;
        NSWindow* m_wnd;
        NSApplication* m_app;

        void init_openGL();
    };
} // namespace pf

#elif defined(PixelForge_OS_Linux)

namespace pf
{
    class Window
    {
    public:
        Window(int width, int height, const wchar_t* name, Color col);
        ~Window();

        Window(const Window &) = delete;
        Window &operator = (const Window &) = delete;

        bool process_message();

        const int width = m_width;
        const int height = m_height;
        const wchar_t* name = m_name;
    
    private:
        const wchar_t* m_name;
        int m_width;
        int m_height;
        Display m_display;
        Window* m_wnd;
        Atom m_delete_msg;

        void init_openGL();
    };
} // namespace pf

#endif // PixelForge_OS_Windows

#endif // PixelForge_WINDOW_HPP