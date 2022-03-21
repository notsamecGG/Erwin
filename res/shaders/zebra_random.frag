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

float line(float val, float center, float size)
{
    return step(center - size, val) - step(center + size, val);
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
    
    vec2 colrow = vec2(10., 5.);
    vec3 color = vec3(0.);
    
	st *= 10.;
    st *= rotate2D(45.);
    
    vec2 fst = fract(st);
    vec2 ist = floor(st);
    
    color = vec3(1. - line(fract(st.x), 0.5, 0.1));
    fst += random(ist);
    color = color + line(fract(fst.y), 0.5, 0.1);


    gl_FragColor = vec4(color,1.0);
}