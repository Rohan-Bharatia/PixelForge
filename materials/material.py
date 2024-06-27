import OpenGL.GL as gl # type: ignore
import OpenGL.GL.shaders as gl.shaders # type: ignore

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

class Material:
    def __init__(self, ambient_color = (0.0, 0.0, 0.0), diffuse_color = (0.0, 0.0, 0.0), specular_color = (0.0, 0.0, 0.0),
                 shininess = 32.0, refractive_index = 0.0, opacity = 1.0, emission_color = (0.0, 0.0, 0.0), diffuse_texture = None,
                 normal_map = None, specular_map = None, opacity_map = None, ambient_occlusion_map = None, metallic = 0.0,
                 roughness = 0.5, normal_mapping_strength = 1.0, alpha_testing = False, alpha_blending = False, double_sided = False,
                 depth_testing = True, depth_writing = True):
        self.ambient_color           = ambient_color
        self.diffuse_color           = diffuse_color
        self.specular_color          = specular_color
        self.shininess               = shininess
        self.refractive_index        = refractive_index
        self.opacity                 = opacity
        self.emission_color          = emission_color
        self.diffuse_texture         = diffuse_texture
        self.normal_map              = normal_map
        self.specular_map            = specular_map
        self.opacity_map             = opacity_map
        self.ambient_occlusion_map   = ambient_occlusion_map
        self.metallic                = metallic
        self.roughness               = roughness
        self.normal_mapping_strength = normal_mapping_strength
        self.alpha_testing           = alpha_testing
        self.alpha_blending          = alpha_blending
        self.double_sided            = double_sided
        self.depth_testing           = depth_testing
        self.depth_writing           = depth_writing
    
    def set_uniforms(self, shader_program):
        shader_program.set_uniform("material.ambient_color", self.ambient_color)
        shader_program.set_uniform("material.diffuse_color", self.diffuse_color)
        shader_program.set_uniform("material.specular_color", self.specular_color)
        shader_program.set_uniform("material.shininess", self.shininess)
        shader_program.set_uniform("material.refractive_index", self.refractive_index)
        shader_program.set_uniform("material.opacity", self.opacity)
        shader_program.set_uniform("material.emission_color", self.emission_color)
        shader_program.set_uniform("material.metallic", self.metallic)
        shader_program.set_uniform("material.roughness", self.roughness)
        shader_program.set_uniform("material.normal_mapping_strength", self.normal_mapping_strength)
        
        # Set the texture(s) if available
        if self.diffuse_texture:
            shader_program.set_uniform("material.diffuse_texture", 0)  # Bind texture unit 0
            self.diffuse_texture.bind(0)

class ShaderProgram:
    def __init__(self, vertex_shader_source = VERT_SHADER, fragment_shader_source = FRAG_SHADER):
        self.program_id = None
        self.vertex_shader_source = vertex_shader_source
        self.fragment_shader_source = fragment_shader_source
        self.uniforms = {}

        # Compile + link gl.shaders
        self.compile_gl.shaders()

    def compile_shaders(self):
         # Compile vertex shader
        vertex_shader = gl.shaders.compileShader(self.vertex_shader_source, gl.GL_VERTEX_SHADER)

        # Compile fragment shader
        fragment_shader = gl.shaders.compileShader(self.fragment_shader_source, gl.GL_FRAGMENT_SHADER)

        # Create shader program
        self.program_id = gl.shaders.compileProgram(vertex_shader, fragment_shader)
    
    def use(self):
        # Use this shader program for rendering
        gl.glUseProgram(self.program_id)

    def set_uniform(self, name, value):
        # Set a uniform variable in the shader program
        if name not in self.uniforms:
            self.uniforms[name] = gl.glGetUniformLocation(self.program_id, name)
            
        location = self.uniforms[name]

        # Determine value type and set uniform
        if isinstance(value, int):
            gl.glUniform1i(location, value)

        elif isinstance(value, float):
            gl.glUniform1f(location, value)

        elif isinstance(value, (tuple, list)):
            if len(value) == 2:
                gl.glUniform2f(location, *value)

            elif len(value) == 3:
                gl.glUniform3f(location, *value)

            elif len(value) == 4:
                gl.glUniform4f(location, *value)
        else:
            raise ValueError(f"Unsupported uniform type for \'{name}\'")

    def delete(self):
        # Delete the shader program and free resources
        if self.program_id:
            gl.glDeleteProgram(self.program_id)
            self.program_id = None