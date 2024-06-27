#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_COLOR_H
#define PixelForge_COLOR_H

namespace pf
{
    class Color
    {
    public:
        Color(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a)
        {
            if(r > 1.0f)
                r = 1.0f;
            if(r < 0.0f)
                r = 0.0f;

            if(g > 1.0f)
                g = 1.0f;
            if(g < 0.0f)
                g = 0.0f;

            if(b > 1.0f)
                b = 1.0f;
            if(b < 0.0f)
                b = 0.0f;

            if(a > 1.0f)
                a = 1.0f;
            if(a < 0.0f)
                a = 0.0f;
        }

        const float r = m_r;
        const float g = m_g;
        const float b = m_b;
        const float a = m_a;
    
    private:
        float m_r;
        float m_g;
        float m_b;
        float m_a;
    };
    
} // namespace pf


#endif // PixelForge_COLOR_H