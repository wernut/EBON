#version 450


uniform vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

out vec4 final_color;

in vec4 outNormal;

void main()
{
	final_color = color;
}