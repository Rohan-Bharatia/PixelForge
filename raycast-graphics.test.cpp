#pragma region LICENSE

// Read the Gnu General Public License v3.0 at: https://www.gnu.org/licenses/gpl-3.0.html

#pragma endregion LICENSE

#pragma once

#ifndef PixelForge_RAYCASTING_TEST_CPP
#define PixelForge_RAYCASTING_TEST_CPP

// std
#include <iostream>
#include <array>
#include <stddef.h>

#include "pf1.h"

std::string vertex = "#version 330 core"
"layout (location = 0) in vec3 position;"
"layout (location = 1) in vec3 m_normal;"
"out vec3 frag_position;"
"out vec3 normal;"
"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 projection;"
"void main()"
"{"
"    frag_position = vec3(model * vec4(position, 1.0));"
"    normal = mat3(transpose(inverse(model))) * m_normal;"
"    gl_Position = projection * view * model * vec4(position, 1.0);"
"}";

std::string fragment = "#version 330 core"
"in vec3 frag_position;"
"in vec3 normal;"
"struct Material"
"{"
"    vec3 ambient_color;"
"    vec3 diffuse_color;"
"    vec3 specular_color;"
"    float shininess;"
"    float refractive_index;"
"    float opacity;"
"    vec3 emission_color;"
"    vec3 diffuse_texture;"
"    vec3 normal_map;"
"    vec3 specular_map;"
"    vec3 opacity_map;"
"    vec3 ambient_occlusion_map;"
"    float metallic;"
"    float roughness;"
"    float normal_mapping_strength;"
"    bool alpha_testing;"
"    bool alpha_blending;"
"    bool double_sided;"
"    bool depth_testing;"
"    bool depth_writing;"
"};"
"uniform Material material;"
"out vec4 FragColor;"
"void main()"
"{"
"    vec3 ambient = material.ambient_color;"
"    vec3 diffuse = material.diffuse_color;"  
"    FragColor = vec4(diffuse, 1.0);"
"}";

int main(int argc, char* argv[])
{
    std::cout << "Creating Window..." << std::endl;
    
    pf::Color bkgnd(0.1, 0.2, 0.3, 1);
    pf::Window* window = new pf::Window(640, 480, L"PixelForge Test Application", bkgnd);

    pf::Camera camera(window, pf::Vec3(0, 0, 0.3), window.width / window.height, 130);
    pf::Graphics graphics(window);

    graphics.set_viewport();
    graphics.set_camera(camera);

    bool running = true;
    while(running)
    {
        if(window->process_message())
        {
            std::cout << "Closing Window..." << std::endl;

            ~window();

            running = false;
        }

        std::array<pf::Primitive, 4> prims;
        pf::BVH bvh(prims);
        std::array<pf::Ray3, 4> rays;

        pf::cuda_intersection(bvh, rays);

        pf::Raycast raycast(rays, 1, 4);
        raycast.cast_rays();
        auto results = raycast.results;

        for(size_t i = 0; i < results.size(); i++)
        {
            std::cout << "Ray " << i << (results[i] ? "Hit" : "Missed") << "An object!" << std::endl;
        }

        Shader shader(vertex, fragment, NULL, pf::Vec3(0.5, 0.5, 0.5));

        graphics.cube(pf::Vec3(-1, -1, -1), 2, 2, 2, pf::draw_style::STATIC);

        graphics.render();

        Sleep(10);
    }

    delete window;
    return 0;
}

#endif // PixelForge_RAYCASTING_TEST_CPP