#version 450

uniform sampler2D ourTexture;

in vec2 texCoords;

out vec4 final_color;

void main()
{
	final_color = texture(ourTexture, texCoords);
}