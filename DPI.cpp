#pragma once

#include <windows.h>

void init_DPI(HWND hwnd)
{
    HDC = GetDC(hwnd);
    g_DPIScaleX = GetDeviceCaps(hdc, LOGPIXELSX) / USER_DEFAULT_SCREEN_DPI;
    g_DPIScaleY = GetDeviceCaps(hdc, LOGPIXELSY) / USER_DEFAULT_SCREEN_DPI;
}