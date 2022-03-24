// Author:
// Title:

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    const float maxIterations = 120.;
    
    st *= 4.;
    
    st -= 2.;
    
    st /= 200000.;
    st -= vec2(0.6405,-0.3595);
    
    
    
    // st -= vec2(0.580,-0.420);
    
    st.x *= u_resolution.x/u_resolution.y;

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

    gl_FragColor = vec4(color,1.0);
}