#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

uniform mat4 MV;
uniform mat4 P;
uniform float time;

out vec3 interpolatedNormal;
out vec2 st;
out vec3 Light;

void main(){
    Light = mat3(MV) * vec3(0.0, 1.0, 1.0);
    gl_Position = (P * MV) * vec4(Position, 1.0);
    interpolatedNormal = mat3(MV) * Normal;
    st = TexCoord;
}
