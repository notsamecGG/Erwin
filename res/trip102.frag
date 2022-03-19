// Author:
// Title:

#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
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

float smoothline(float val, float center, float size, float smoothness)
{
    return smoothstep(center - size, center - size, val) - smoothstep(center + size * smoothness, center + size, val);
}

mat2 rotate2D(float angle)
{
    return mat2(
        cos(angle), -sin(angle),
        sin(angle),  cos(angle)
    );
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    st.x *= u_resolution.x/u_resolution.y;
    
    vec2 colrow = vec2(10.);
    vec3 color = vec3(0.);
    
	st *= colrow;
    st += noise(st * 0.300);
    
    st -= colrow / 2.;
    st = rotate2D(u_time / 10.) * st;
    st += colrow / 2.;
    
    st *= rotate2D(noise(vec2(sin(u_time))) * 0.001 * u_time);
    
    vec2 fst = fract(st);
    vec2 ist = floor(st);
    
    vec3 yellow = vec3(1., 1., 0.);
    vec3 magenta = vec3(1., 0., 1.);
    
	color = step(min(1., abs(sin(noise(ist) * u_time * 3.14 * 0.156)) + 0.3) , mix(yellow, magenta, distance(fst, vec2(0.5))));
    //color = vec3(st, 0.);
    
    gl_FragColor = vec4(color,1.0);
}