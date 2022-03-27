// Author: Sam GG
// Title: 

#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359

in vec3 v_pos;

uniform ivec2 u_resolution;
uniform vec2 u_position;
uniform float u_time;

void main() {
    vec2 st = v_pos.xy;
    float ratio = u_resolution.x/u_resolution.y;
    float maxIterations = floor(u_time);
    
    st.x *= ratio;
    
    st *= 4.;

    st /= max(1., u_time - 2.);
    // st -= u_position;
    st -= vec2(0.740,-0.090) + vec2(0.820,0.570) * 0.01;
    
    float a = st.x;
    float b = st.y;
    
    float z = 0.;
    for (float i = 0.; i < maxIterations; i++)
    {
        float aa = pow(a, 2.) - pow(b, 2.);
        float bb = 2. * a * b;
        
        a = aa + st.x;
        b = bb + st.y;
        
        if (pow(aa, 2.) + pow(bb, 2.) > 16.)
            break;
        
        z = i;
    }
    
    float brightness = z;
    
    if (z >= maxIterations - 1.)
        brightness = 0.; 
    
    vec3 color = vec3(0.);
    color = vec3(brightness) / maxIterations;
    color = vec3(brightness, brightness, 0.) * brightness / maxIterations;

    gl_FragColor = vec4(color,1.0);
}