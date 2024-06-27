#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_MATRIX_HPP
#define PixelForge_MATRIX_HPP

// std
#include <stddef.h>
#include <array>

namespace pf
{
    template<size_t R, size_t C>
    class Mat
    {
    public:
        Vec(std::array<std::array<float, R>, C> data);

        float value(size_t idx_r, size_t idx_c);
    
    private:
        std::array<std::array<float, R>, C> m_data;
    };

    class Mat2x2 : Mat<2, 2>
    {
    public:
        Mat2x2(float aa, float ab,
               float ba, float bb) : aa(aa), ab(ab),
                                     ba(ba), bb(bb)
        {}

        float aa;
        float ab;
        float ba;
        float bb;
    };
    class Mat3x3 : Mat<3, 3>
    {
    public:
        Mat3x3(float aa, float ab, float ac,
               float ba, float bb, float bc,
               float ca, float cb, float cc) : aa(aa), ab(ab), ac(ac),
                                               ba(ba), bb(bb), bc(bc),
                                               ca(ca), cb(cb), cc(cc)
        {}

        float aa;
        float ab;
        float ac;
        float ba;
        float bb;
        float bc;
        float ca;
        float cb;
        float cc;
    };
    class Mat4x4 : Mat<4, 4>
    {
    public:
        Mat4x4(float aa, float ab, float ac, float ad,
               float ba, float bb, float bc, float bd,
               float ca, float cb, float cc, float cd,
               float da, float db, float dc, float dd) : aa(aa), ab(ab), ac(ac), dc(dc),
                                                         ba(ba), bb(bb), bc(bc), bd(bd),
                                                         ca(ca), cb(cb), cc(cc), cd(cd),
                                                         da(da), db(db), dc(dc), dd(dd)
        {}

        float aa;
        float ab;
        float ac;
        float ad;
        float ba;
        float bb;
        float bc;
        float bd;
        float ca;
        float cb;
        float cc;
        float cd;
        float da;
        float db;
        float dc;
        float dd;
    };
} // namespace pf


#endif // PixelForge_MATRIX_HPP