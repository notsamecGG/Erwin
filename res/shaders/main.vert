#version 330 core

layout (location = 0) in vec3 a_pos;

out vec3 v_pos;

void main()
{
    gl_Position = vec4(a_pos, 1.0);

    v_pos = a_pos;
}