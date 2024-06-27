import material

vertex = """
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 m_normal;

out vec3 frag_position;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    frag_position = vec3(model * vec4(position, 1.0));
    normal = mat3(transpose(inverse(model))) * m_normal;

    gl_Position = projection * view * model * vec4(position, 1.0);
}
"""

fragment = """
#version 330 core

in vec3 frag_position;
in vec3 normal;

struct Material
{
    vec3 ambient_color;
    vec3 diffuse_color;
    vec3 specular_color;
    float shininess;
    float refractive_index;
    float opacity;
    vec3 emission_color;
    vec3 diffuse_texture;
    vec3 normal_map;
    vec3 specular_map;
    vec3 opacity_map;
    vec3 ambient_occlusion_map;
    float metallic;
    float roughness;
    float normal_mapping_strength;
    bool alpha_testing;
    bool alpha_blending;
    bool double_sided;
    bool depth_testing;
    bool depth_writing;
};

uniform Material material;

out vec4 FragColor;

void main()
{
    vec3 ambient = material.ambient_color;
    vec3 diffuse = material.diffuse_color;
    
    FragColor = vec4(diffuse, 1.0);
}
"""

GREEN = material.Material(diffuse_color=(0.0, 0.75, 0.0))

shader_program = material.ShaderProgram(vertex, fragment)

shader_program.use()
GREEN.set_uniforms(shader_program)