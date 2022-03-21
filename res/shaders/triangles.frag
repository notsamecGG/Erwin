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
    return sin(val * 1000000.);
}

float random(vec2 val)
{
	return fract(sin(dot(val.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void main() {
    vec2 st = v_pos.xy + vec2(0.5);
    vec2 center = vec2(0.5);
    float distance = 0.;
    
    st.x *= u_resolution.x/u_resolution.y;
    
    st *= 10.;
    vec2 fst = fract(st);
    vec2 ist = floor(st);
    
    fst -= center;
    
    //float radius = distance(st, center);
    float angle = atan(fst.y, fst.x) + PI;
    float radius = 2. * PI / 3.;

    vec3 color = vec3(0.);
    
    angle += u_time * random(ist);
    
    distance = cos(floor(angle/radius));
    distance = cos(floor(.5 + angle/radius) * radius - angle) * length(fst);
    color = vec3(smoothstep(.2, .25, distance));
    // color = vec3(ist.x / 10.);
    // color = vec3(st, 0.);

    gl_FragColor = vec4(color,1.0);
}