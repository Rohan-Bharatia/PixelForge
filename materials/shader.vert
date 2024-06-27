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