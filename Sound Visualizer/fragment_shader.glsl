#version 330 core

in vec3 vs_position;
in float height_scale;

out vec4 color;

void main()
{
	//Red/green vectors to blend with
	vec3 green = vec3(0.f, 1.f, 0.f);
	vec3 red = vec3(1.f, 0.f, 0.f);

	//Calculate interpolation factor with regards to mirrored geometry
	float u;

	if(vs_position.y > 0)
	{
		u = vs_position.y/height_scale;
	}
	else
	{
		u = -1*vs_position.y/height_scale;
	}

	color = vec4(mix(green, red, u), 1.0);
}