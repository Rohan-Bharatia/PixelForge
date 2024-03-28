#pragma once

#include <windows.h>

HRESULT result = CoInitializeEx(NULL, COINIT_APARTAMENTTHREADED | COINIT_DISABLE_OLE1DDE);
