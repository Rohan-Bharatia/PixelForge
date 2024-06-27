#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_CAMERA_CPP
#define PixelForge_CAMERA_CPP

#include "include/camera.hpp"

// std
#include <cmath>
#include <cassert>

float d2r(float deg)
{
    return deg * (180 / (std::asin(1) * 2));
}

namespace pf
{

    Camera::Camera(Window* window, Vec3& position, float* aspect_ratio, float FOV) : m_window(window), m_position(position),
                                                                                     m_aspect_ratio(aspect_ratio), m_FOV(FOV),
                                                                                     m_up(Vec3(0, 0, 1)), m_front(Vec3(0, 0, 0)),
                                                                                     m_right(cross(m_up, m_up))
    {
        Vec3 front(std::cos(d2r(m_yaw)) * std::cos(d2r(m_pitch)),
                   std::cos(d2r(m_pitch)),
                   std::cos(d2r(m_yaw)) * std::cos(d2r(m_pitch)));
        front = normalize(front);

        m_right = normalize(cross(m_front, m_up));
        m_up = normalize(cross(m_right, front));
    }

    void Camera::set_aspect_ratio(float* aspect_ratio)
    {
        m_aspect_ratio = aspect_ratio;
    }

    void Camera::set_FOV(float FOV)
    {
        m_FOV = FOV;
    }
    
    Mat4x4 Camera::view_matrix() const
    {
        const Vec3 eye = m_position;
        const Vec3 center(m_position.x + m_front.x,
                          m_position.y + m_front.y,
                          m_position.z + m_front.z);

        Vec3 f(center.x - eye.x,
               center.y - eye.y,
               center.z - eye.z);
        f = normalize(f);
        Vec3 s = normalize(cross(f, normalize(m_up)));
        Vec3 u = cross(s, f);

        return Mat4x4(s.x, u.x, -f.x, 1,
                      s.y, u.y, -f.y, 1,
                      s.z, u.z, -f.z, 1,
                      -dot(s, eye), -dot(u, eye), -dot(f, eye), 1);
    }

    Mat4x4 Camera::projection_matrix() const
    {
        const float near = 0.1;
        const float far = 100;
        const float FOV = std::tan(m_FOV / 2);
        
        return Mat4x4(1 / (m_aspect_ratio * FOV), 0, 0, 0,
                      0, 1 / FOV, 0, 0,
                      0, 0, -(far + near) / (far - near), -1,
                      0, 0, -(2 * far * near) / (far - near), 0);
    }

    void Camera::move(Vec3& target)
    {
        m_position.x += target.x;
        m_position.y += target.y;
        m_position.z += target.z;
    }

    void Camera::look_at(Vec3& target)
    {
        Vec3 a(target.x - m_position.x,
               target.y - m_position.y,
               target.z - m_position.z);
        m_front = normalize(a);
        m_right = normalize(m_right);
    }

    void Camera::rotate(float roll, float yaw, float pitch) : m_roll(roll), m_yaw(yaw), m_pitch(pitch)
    {   
        *this = Mat4x4(std::cos(roll) * std::cos(yaw) * std::cos(pitch), -std::sin(roll) * -std::sin(yaw) * -std::sin(pitch), 3, 3,
                       std::sin(roll) * std::sin(yaw) * std::sin(pitch), std::cos(roll) * std::cos(yaw) * std::cos(pitch), 3, 3,
                       3, 3, 3, 3,
                       3, 3, 3, 3);
    }

    Vec3 Camera::normalize(Vec3& n) const
    {
        float norm = std::sqrt(n.x * n.x + n.y * n.y + n.z * n.z);

        assert(norm == 0 && "Unable to divide a \'Vec3\' by 0\n");

        return Vec3(n.x / norm,
                    n.y / norm,
                    n.z / norm);
    }

    Vec3 Camera::cross(Vec3& a, Vec3& b) const
    {
        return Vec3(a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x);
    }

    float Camera::dot(Vec3& a, Vec3& b) const
    {
        return ((a.x * b.x) +
                (a.y * b.y) +
                (a.z * b.z));
    }
} // namespace pf

#endif // PixelForge_CAMERA_CPP