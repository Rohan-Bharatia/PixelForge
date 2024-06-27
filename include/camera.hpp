#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_CAMERA_HPP
#define PixelForge_CAMERA_HPP

#include "vector.hpp"
#include "matrix.hpp"
#include "window.hpp"

namespace pf
{
    class Camera
    {
    public:
        Camera(Window* window, Vec3& position, float* aspect_ratio, float FOV);

        void set_aspect_ratio(float* aspect_ratio);
        void set_FOV(float FOV);

        Mat4x4 view_matrix() const;
        Mat4x4 projection_matrix() const;

        void move(Vec3& target);
        void look_at(Vec3& target);
        void rotate(float roll, float yaw, float pitch);

        const float* aspect_ratio = m_aspect_ratio;
        const float FOV = m_FOV;
    
    private:
        Window* m_window;
        Vec3 m_position;
        Vec3 m_up;
        Vec3 m_front;
        Vec3 m_right;
        float* m_aspect_ratio;
        float m_FOV;
        float m_roll;
        float m_yaw;
        float m_pitch;

        Vec3 normalize(Vec3& n) const;
        Vec3 cross(Vec3& a, Vec3& b) const;
        float dot(Vec3& a, Vec3& b) const;
    };
} // namespace pf


#endif // PixelForge_CAMERA_HPP