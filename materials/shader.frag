#330 core

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

void main()
{
    vec3 ambient = material.ambient_color;
    vec3 diffuse = material.diffuse_color;
    vec3 specular = material.specular_color;
    vec3 norm = normalize(normal);
    vec3 light_direction = normalize(vec3(0.0, 0.0, -1.0));
    vec3 view_direction = normalize(vec3(0.0, 0.0, 1.0) - frag_position);
    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse_color = diff * diffuse;
    vec3 reflect_direction = reflect(-light_direction, norm);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
    vec3 specular_color = specular * spec;
    vec3 result = (ambient + diffuse_color) + specular_color;
    
    FragColor = vec4(result, material.opacity);
}