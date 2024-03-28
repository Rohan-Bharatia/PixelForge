#include <windows.h>
#include <shobjidl.h>
#include <atlbase.h>

void WINAPI win_main(HINSTANCE instance, HINSTANCE, PWSTR line, int show)
{
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    if(SUCCEEDED(hr))
    {
        CComPtr<IFileOpenDialog> file;
        hr = file.CoCreateInstance(__uuidof(FileOpenDialog));

        if(SUCCEEDED(hr))
        {
            hr = file -> Show(NULL);

            if(SUCCEEDED(hr))
            {
                CComPtr<IShellItem> item;
                hr = file -> GetResult(item);

                if(SUCCEEDED(hr))
                {
                    PWSTR path;
                    hr = item -> GetDisplayName(SIGDN_FILESYSPATH, path);

                    if(SUCCEEDED(hr))
                    {
                        MessageBox(NULL, path, L"File Path", MB_OK);
                        CoTaskMemFree(path);
                    }
                }
            }
        }

        CoUninitialize();
    }

    return;
}

template <class T> safe_release(T **tmp)
{
    if(*tmp)
    {
        (*tmp) -> Release();
        *tmp = NULL;
    }
}

HRESULT show_dialog()
{
    IFileOpenDialog *file = NULL;
    IShellItem *item = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(FileOpenDialog), NULL, CLSCTX_INPROC_SERVER,
                                  IID_PPV_ARGS(&file));
    
    if(FAILED(hr))
        goto release;
    
    hr = file -> Show(NULL);

    if(FAILED(hr))
        goto release;

release:
    safe_release(&item);
    safe_release(&file);

    return hr;
}
printf(show_dialog());