#version 450

uniform vec4 color 	= vec4(1, 1, 1, 1);

out vec4 final_color;

in vec4 outNormal;

void main()
{
	vec4 modNormal = outNormal;
	modNormal.x += sin(50);
	final_color = modNormal;
}