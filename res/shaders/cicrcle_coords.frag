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

void main() {
    vec2 st = v_pos.xy + vec2(0.5);

    vec2 center = vec2(0.5);
    float distance = 0.;
    
    st.x *= u_resolution.x/u_resolution.y;
    st -= center;
    
    //float radius = distance(st, center);
    float angle = atan(st.y, st.x) + PI;
    float radius = 2. * PI / 3.;

    vec3 color = vec3(0.);
    vec2 pos = vec2(radius, angle);
    
    distance = cos(floor(angle/radius));
    distance = cos(floor(angle/radius) * radius - angle) * length(st);
    color = vec3(distance);
    // color = vec3(pos, 0.);
    // color = vec3(st, 0.);

    gl_FragColor = vec4(color,1.0);
}