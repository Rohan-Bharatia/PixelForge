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
    vec3 albedo = material.diffuse_color;
    vec3 specular = material.specular_color;
    vec3 view_dir = normalize(vec3(0.0, 0.0, 1.0) - frag_position);
    vec3 norm = normalize(normal);
    vec3 reflect_dir = reflect(-view_dir, norm);
    vec3 ambient_result = ambient * albedo;
    float NdotV = max(dot(norm, view_dir), 0.0);
    float specularity = pow(max(dot(reflect_dir, view_dir), 0.0), material.shininess);
    vec3 specular_result = specular * specularity * material.metallic;
    
    FragColor = vec4(ambient_result + specular_result, 1.0);
}
"""

METALLIC_CHARTREUSE = material.Material(ambient_color = (0.0, 0.1, 0.0), diffuse_color = (0.0, 1.0, 0.0),
                                       specular_color = (1.0, 1.0, 1.0), shininess = 64.0, metallic = 1.0)

shader_program = material.ShaderProgram(vertex, fragment)

shader_program.use()
METALLIC_CHARTREUSE.set_uniforms(shader_program)