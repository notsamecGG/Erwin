#version 330 core

uniform float u_time;

void main()
{
    float val = (sin(u_time * 3.14) + 1.) / 2.;

    vec3 color = vec3(val);

    gl_FragColor = vec4(color, 1.0);
}