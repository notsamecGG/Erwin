#version 330 core

in vec3 v_pos;

uniform float u_time;
uniform vec2 u_resolution;

float smoothrect(vec2 st, vec2 center, vec2 size, float smoothness)
{
    vec2 res_smoothness = vec2(smoothness);
    res_smoothness.x *= size.x / size.y; 
    
    vec2 rect_vec = smoothstep(center - size, center - size - smoothness, st) - smoothstep(center + size + smoothness, center + size, st); 
    
    return rect_vec.x * rect_vec.y;
}

void main()
{
    vec2 st = v_pos.xy + vec2(0.5);
    vec2 center = vec2(0.5);
    
    st.x *= u_resolution.x/u_resolution.y;

    vec3 color = vec3(0.);
    float rect_color = smoothrect(st, vec2(0.5), vec2(0.45, 0.4), 0.1);
    color = vec3(step(0.5, rect_color));

    gl_FragColor = vec4(color, 1.);
}