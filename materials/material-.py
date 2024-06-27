import material

VERT_SHADER = """
#330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 m_normal;

out vec3 frag_position;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    frag_position = vec3(model * vec4(m_normal, 1.0));
    normal = mat3(transpose(inverse(model))) * m_normal;

    gl_Position = projection * view * model * vec4(m_normal, 1.0);
}
"""

FRAG_SHADER = """
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
"""

class Shader:
    def __init__(self, vertex_shader_source = VERT_SHADER, fragment_shader_source = FRAG_SHADER, ambient_color = (0.0, 0.0, 0.0),
                 diffuse_color = (0.0, 0.0, 0.0), specular_color = (0.0, 0.0, 0.0), shininess = 32.0, refractive_index = 0.0,
                 opacity = 1.0, emission_color = (0.0, 0.0, 0.0), diffuse_texture = None, normal_map = None, specular_map = None,
                 opacity_map = None, ambient_occlusion_map = None, metallic = 0.0,roughness = 0.5, normal_mapping_strength = 1.0,
                 alpha_testing = False, alpha_blending = False, double_sided = False, depth_testing = True, depth_writing = True):

        self.MATERIAL = material.Material(ambient_color, diffuse_color, specular_color, shininess, refractive_index, opacity, emission_color,
                                          diffuse_texture, normal_map, specular_map, opacity_map, ambient_occlusion_map, metallic, roughness,
                                          normal_mapping_strength, alpha_testing, alpha_blending, double_sided, depth_testing, depth_writing);
        self.SHADER = material.ShaderProgram(vertex_shader_source, fragment_shader_source);

        self.SHADER.use();
        self.MATERIAL.set_uniforms();

    def get_material(self):
        return self.MATERIAL
    def get_shader(self):
        return self.SHADER