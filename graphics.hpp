#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_GRAPHICS_HPP
#define PixelForge_GRAPHICS_HPP

#include "camera.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "window.hpp"

#if defined(PixelForge_OS_Windows)

namespace pf
{
    enum class draw_style
    {
        STATIC,
        STREAM,
        DYNAMIC
    };

    class Graphics
    {
    public:
        Graphics(Window* Window);

        void set_viewport();
        void set_camera(Camera& camera);

        bool render();

        void cube(Vec3& point, float width, float height, float depth, draw_style ds = draw_style::STREAM);
        void sphere(Vec3& point, float radius, draw_style ds = draw_style::STREAM);
        void pyramid(Vec3& point, float base_width, float height, draw_style ds = draw_style::STREAM);
        void cylinder(Vec3& point, float radius, float height, draw_style ds = draw_style::STREAM);
        void cone(Vec3& point, float base_radius, float height, draw_style ds = draw_style::STREAM);
    
    private:
        enum class primitives
        {
            CUBE,
            SPHERE,
            PYRAMID,
            CYLINDER,
            CONE
        };

        Window* m_window;
        Camera m_camera;
        GLuint m_vertex_array;
        GLuint m_vertex_buffer;
        primitives m_primitive;
        draw_style m_ds;
        Vec3 m_point;
        float m_width;
        float m_height;
        float m_depth;
        float m_radius;
        float m_segments;
        int m_vertex_count;

        void setup_buffers();

        void draw_primitive();
    };
} // namespace pf

#endif // defined(PixelForge_OS_Windows)

#endif // PixelForge_GRAPHICS_HPP