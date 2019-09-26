#version 330 core

uniform float time;

in vec3 interpolatedNormal;
in vec3 Light;

out vec4 color;

void main() {
     vec3 nNormal = normalize(interpolatedNormal);
     float diffuse = max(0.0, dot(nNormal, Light));
     //Only ambient light for now
//     color = texcolor;
}


//void main() {
//  vec3 green = vec3(0.0, 1.0, 0.0);
//  vec3 brown =  vec3(0.5, 0.25, 0.0);
//  float edge = step(st.t + 0.1*perlinnoise(st*5.0), 0.7);
//  vec3 pattern = mix(green, brown, edge);
//  gl_FragColor = vec4(pattern, 1.0);
//}
