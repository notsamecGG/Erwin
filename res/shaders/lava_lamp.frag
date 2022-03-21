// Author: Sam GG
// Title: 

#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359

in vec3 v_pos;

uniform vec2 u_resolution;
uniform float u_time;

float random(float val)
{
    return fract(10000. * sin(val));
}

float random(vec2 val)
{
    return fract(sin(dot(val,
            vec2(12.9898,78.233)))*
        43758.5453123);
}

// Based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

mat2 rotate2D(float angle)
{
    return mat2(
        cos(angle), -sin(angle),
        sin(angle),  cos(angle)
    );
}

void main() {
    vec2 st = v_pos.xy + vec2(0.5);
    st.x *= u_resolution.x/u_resolution.y;
    st *= 0.104 * 100.;

    vec3 color = vec3(0.);
	st += vec2(u_time);
    st *= rotate2D(-70.);
    float n1 = noise(st);
    st *= rotate2D(70.);
    st -= vec2(u_time);
    
    st += vec2(u_time * 0.02, n1);
    st *= rotate2D(40.);
    float n2 = noise(st);
    st += vec2(u_time * 0.116, 0.);
    float n3 = noise(st);
    
    color = vec3(step(0.896, fract(n3 + n2)));

    gl_FragColor = vec4(color,1.0);
}