#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_GRAPHICS_HPP
#define PixelForge_GRAPHICS_HPP

#include "include/graphics.hpp"
#include "include/window.hpp"
#include "config/openGL.h"

#if defined(PixelForge_OS_Windows)

// std
#include <windef.h>
#include <cmath>

class wnd : private Window
{};

namespace pf
{
    Graphics::Graphics(Window* Window) : m_window(window)
    {}

    void Graphics::set_viewport()
    {
        glViewport(0, 0, m_window.width, m_window.height);
    }
    
    void Graphics::set_camera(Camera& camera) : m_camera(camera)
    {}

    bool Graphics::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Mat4x4 view    = m_camera.view_matrix();
        Mat4x4 project = m_camera.projection_matrix();

        SwapBuffers(GetDC(wnd::m_hwnd));
    }

    void Graphics::cube(Vec3& point, float width, float height, float depth, draw_style ds = draw_style::STREAM) : m_point(point), m_width(width),
                                                                                                                   m_height(height), m_depth(depth),
                                                                                                                   m_ds(ds)
    {
        point.x /= m_window.width;
        point.y /= m_window.height;
        point.z /= m_window.width * m_window.height;
        width /= m_window.width;
        height /= m_window.height;
        depth /= m_window.width * m_window.height;

        m_primitive = primitives::CUBE;
        
        glBindVertexArray(m_vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);

        glGenVertexArray();

        setup_buffers();
        draw_primitive();
    }
    
    void Graphics::sphere(Vec3& point, float radius, draw_style ds = draw_style::STREAM) : m_point(point), m_radius(radius), m_ds(ds)
    {
        point.x /= m_window.width;
        point.y /= m_window.height;
        point.z /= m_window.width * m_window.height;
        radius /= m_window.width * m_window.height;

        m_primitive = primitives::SPHERE;
        
        glBindVertexArray(m_vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);

        glGenVertexArray();

        setup_buffers();
        draw_primitive();
    }
    
    void Graphics::pyramid(Vec3& point, float base_width, float height, draw_style ds = draw_style::STREAM) : m_point(point), m_width(base_width),
                                                                                                               m_ds(ds)
    {
        point.x /= m_window.width;
        point.y /= m_window.height;
        point.z /= m_window.width * m_window.height;
        base_radius /= m_window.width;
        height /= m_window.height;

        m_primitive = primitives::PYRAMID;
        
        glBindVertexArray(m_vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);

        glGenVertexArray();

        setup_buffers();
        draw_primitive();
    }
    
    void Graphics::cylinder(Vec3& point, float radius, float height, draw_style ds = draw_style::STREAM) : m_point(point), m_radius(base_radius),
                                                                                                           m_height(height), m_ds(ds)
    {
        point.x /= m_window.width;
        point.y /= m_window.height;
        point.z /= m_window.width * m_window.height;
        radius /= m_window.width;
        height /= m_window.height;

        m_primitive = primitives::CYLINDER;
        
        glBindVertexArray(m_vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);

        glGenVertexArray();

        setup_buffers();
        draw_primitive();
    }
    
    void Graphics::cone(Vec3& point, float base_radius, float height, draw_style ds = draw_style::STREAM) : m_point(point), m_radius(radius),
                                                                                                            m_height(height), m_ds(ds)
    {
        point.x /= m_window.width;
        point.y /= m_window.height;
        point.z /= m_window.width * m_window.height;
        base_radius /= m_window.width;
        height /= m_window.height;

        m_primitive = primitives::CONE;
        
        glBindVertexArray(m_vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);

        glGenVertexArray();

        setup_buffers();
        draw_primitive();
    }

    void Graphics::setup_buffers()
    {
        std::array<GLfloat, 1000> verticies;

        switch(m_primitive)
        {
        case primitives::CUBE: // 72 Indicies - 24 Verticies - 6 Faces
            verticies =
            {
                // Front face
                m_point.x - m_width / 2, m_point.y - m_height / 2, m_point.z + m_depth / 2,
                m_point.x + m_width / 2, m_point.y - m_height / 2, m_point.z + m_depth / 2,
                m_point.x + m_width / 2, m_point.y + m_height / 2, m_point.z + m_depth / 2,
                m_point.x - m_width / 2, m_point.y + m_height / 2, m_point.z + m_depth / 2,

                // Back face
                m_point.x - m_width / 2, m_point.y - m_height / 2, m_point.z - m_depth / 2,
                m_point.x + m_width / 2, m_point.y - m_height / 2, m_point.z - m_depth / 2,
                m_point.x + m_width / 2, m_point.y + m_height / 2, m_point.z - m_depth / 2,
                m_point.x - m_width / 2, m_point.y + m_height / 2, m_point.z - m_depth / 2,

                // Left face
                m_point.x - m_width / 2, m_point.y - m_height / 2, m_point.z - m_depth / 2,
                m_point.x - m_width / 2, m_point.y - m_height / 2, m_point.z + m_depth / 2,
                m_point.x - m_width / 2, m_point.y + m_height / 2, m_point.z + m_depth / 2,
                m_point.x - m_width / 2, m_point.y + m_height / 2, m_point.z - m_depth / 2,

                // Right face
                m_point.x + m_width / 2, m_point.y - m_height / 2, m_point.z - m_depth / 2,
                m_point.x + m_width / 2, m_point.y - m_height / 2, m_point.z + m_depth / 2,
                m_point.x + m_width / 2, m_point.y + m_height / 2, m_point.z + m_depth / 2,
                m_point.x + m_width / 2, m_point.y + m_height / 2, m_point.z - m_depth / 2,

                // Top face
                m_point.x - m_width / 2, m_point.y + m_height / 2, m_point.z + m_depth / 2,
                m_point.x + m_width / 2, m_point.y + m_height / 2, m_point.z + m_depth / 2,
                m_point.x + m_width / 2, m_point.y + m_height / 2, m_point.z - m_depth / 2,
                m_point.x - m_width / 2, m_point.y + m_height / 2, m_point.z - m_depth / 2,

                // Bottom face
                m_point.x - m_width / 2, m_point.y - m_height / 2, m_point.z + m_depth / 2,
                m_point.x + m_width / 2, m_point.y - m_height / 2, m_point.z + m_depth / 2,
                m_point.x + m_width / 2, m_point.y - m_height / 2, m_point.z - m_depth / 2,
                m_point.x - m_width / 2, m_point.y - m_height / 2, m_point.z - m_depth / 2
            };

            break;
        
        case primitives::SPHERE: // 3072 Indicies - 1024 Verticies - 128 Faces
            const int segments = 32;
            const int rings = 32;

            for(int ring = 0; ring <= rings; ring++)
            {
                const float theta = ring * (std::asin(1) * 2) / segments;

                for(int segment = 0; segment <= segments; segment++)
                {
                    const float phi = segment * (std::asin(1) * 4) / segments;

                    Vec3 p(std::cos(phi) * std::sin(theta),
                           std::cos(theta),
                           std::sin(phi) * std::cos(theta));

                    // Faces
                    for(int i = 0; i < segments * rings; i++)
                    {
                        verticies[i + 0] = m_point.x + m_radius * p.x;
                        verticies[i + 1] = m_point.y + m_radius * p.y;
                        verticies[i + 2] = m_point.z + m_radius * p.z;
                    }
                }
            }

            break;

        case primitives::PYRAMID: // 15 Indicies - 5 Verticies - 5 Faces
            verticies =
            {
                // Base face
                m_point.x - m_width / 2, m_point.y - m_height / 2, m_point.z - m_width / 2,
                m_point.x + m_width / 2, m_point.y - m_height / 2, m_point.z - m_width / 2,
                m_point.x + m_width / 2, m_point.y - m_height / 2, m_point.z + m_width / 2,
                m_point.x - m_width / 2, m_point.y - m_height / 2, m_point.z + m_width / 2,

                // Apex vertex
                m_point.x, m_point.y + m_height / 2, m_point.z
            };

            break;
        
        case primitives::CYLINDER: // 192 Indicies - 64 Verticies - 34 Faces
            const float segments = 32;
            const float step = (std::asin(1) * 4) / segments;

            for(int segment = 0; segment < segments; segment++)
            {
                const float angle = segment * step;

                // Top face
                for(int i = 0; i < segments; i++)
                {
                    verticies[i + 0] = m_point.x + m_radius * std::cos(angle);
                    verticies[i + 1] = m_point.y + m_height;
                    verticies[i + 2] = m_point.z + m_radius * std::sin(angle);
                }

                // Bottom face
                for(int i = segments; i < segments * 2; i++)
                {
                    verticies[segments + i + 0] = m_point.x + m_radius * std::cos(angle);
                    verticies[segments + i + 1] = m_point.y;
                    verticies[segments + i + 2] = m_point.z + m_radius * std::sin(angle);
                }
            }

            break;
        
        case primitives::CONE: // 99 Indicies - 33 Verticies - 33 Faces
            const float segments = 32;

            for(int segment = 0; segment < segments; segment++)
            {
                const float angle = segment * step;

                // Top face
                for(int i = 0; i < segments; i++)
                {
                    verticies[i + 0] = m_point.x + m_radius * std::cos(angle);
                    verticies[i + 1] = m_point.y + m_height;
                    verticies[i + 2] = m_point.z + m_radius * std::sin(angle);
                }

                // Apex vertex
                verticies[segments + 0] = m_point.x;
                verticies[segments + 1] = m_point.y + m_height;
                verticies[segments + 2] = m_point.z;
            }
            
            break;
        
        default:
            for(int i = 0; i < verticies.size(); i++)
                verticies[i] = NULL;
            
            break;
        }

            for(int i = 0; i < verticies.size(); i++)
            {
                if(verticies[i] != NULL)
                    m_vertex_count++;
            }

        glGenVertexArrays(1, &m_vertex_array);
        glBindVertexArray(m_vertex_array);

        glGenBuffers(GL_ARRAY_BUFFER, m_vertex_array);

        switch(m_ds)
        {
        case draw_style::STATIC:
            glBufferData(GL_ARRAY_BUFFER, m_vertex_count, verticies, GL_STATIC_DRAW);

            break;
        
        case draw_style::STREAM:
            glBufferData(GL_ARRAY_BUFFER, m_vertex_count, verticies, GL_STREAM_DRAW);

            break;
        
        case draw_style::DYNAMIC:
            glBufferData(GL_ARRAY_BUFFER, m_vertex_count, verticies, GL_DYNAMIC_DRAW);

            break;
        
        default:
            glBufferData(NULL, NULL, NULL, NULL);

            break;
        }

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, static_cast<GLvoid*>(0));
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void Graphics::draw_primitive()
    {
        glBindVertexArray(m_vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);
        glBindVertexArray(0);
    }
} // namespace pf

#endif // defined(PixelForge_OS_Windows)

#endif // PixelForge_GRAPHICS_HPP