#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Color;

uniform mat4 M;
uniform mat4 P;
uniform mat4 V;
uniform float scale;

out vec3 vs_position;
out float height_scale;

void main()
{
	height_scale = scale;
	vs_position = Position;
    gl_Position = (P * V * M) * vec4(Position, 1.f);
}
