#version 330 core

uniform float time;

in vec3 vs_position;
in vec3 vs_color;
in float height_scale;

out vec4 color;

void main()
{
	vec3 green = vec3(0.f, 1.f, 0.f);
	vec3 red = vec3(1.f, 0.f, 0.f);

	float u = vs_position.y/height_scale;	
	//Add calculations for color depending on amplitude
	color = vec4((green * (1-u)) + (red * u), 1.0);
}