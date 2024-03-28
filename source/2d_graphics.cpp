#include "include/2d_graphics.h"
#include "include/color.h"
#include <pf1.h>
#include <d2d1.h>
#include "COM.cpp"
using namespace D2D1;

void graphics::triangle(vec2 a, vec2 b, vec2 c, Color col)
{
    ID2D1_TRIANGLE tri = NULL;
    HRESULT hr1 = S_OK;

    if(render_target == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = SizeU(rc.right, rc.bottom);

        hr1 = factory -> CreateRenderTarget(RenderTargetProperties(),
                                            HwndRenderTargetProperties(m_hwnd, size),
                                            &render_target);
        if(SUCCEEDED(hr1))
        {
            const col1 = ColorF(col.red, col.green, col.blue);

            if(SUCCEEDED(hr1))
            {
                if(render_target != NULL)
                {
                tri = Triangle(Point2F(a.x, a.y),
                            Point2F(b.x, b.y),
                            Point2F(c.x, c.y));
                }
            }
        }
    }

    HRESULT hr2;
    PAINTSTRUCT ps;
    
    if(SUCCEEDED(hr))
    {    
        BeginPaint(m_hwnd, &ps);

        render_target -> BeginPaint();
        render_target -> Clear(ColorF(m_col.red, m_col.green, m_col.blue));
        render_target -> FillTriangle(tri, brush);
        hr2 = render_target -> EndDraw();

        if(FAILED(hr2) || hr == D2DERR_RECREATE_TARGET)
        {
            safe_release(&render_target);
            safe_release(&brush);
        }

        EndPaint(m_hwnd, &ps);
    }
}

void graphics::resize()
{
    if(render_target != NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);
        D2D1_SIZE_U size = SizeU(rc.right, rc.bottom);

        render_target->resize(size);

        if(render_target != NULL)
        {
            tri = Triangle(Point2F(a.x, a.y),
                           Point2F(b.x, b.y),
                           Point2F(c.x, c.y));
        }

        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}
