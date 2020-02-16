#version 450

uniform vec4 color 	= vec4(1, 1, 1, 1);

out vec4 final_color;

in vec2 textCoords;
uniform sampler2D ourTexture;

void main()
{
	//final_color = color;
	final_color = texture(ourTexture, textCoords);
}