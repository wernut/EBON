#version 450

#define PI 3.1415926535897932384626433832795

layout(location = 0) in vec3 local_position;
layout(location = 1) in vec4 normal;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform float time;
uniform float adjust;

out vec4 outNormal;

float line = 0.25f;

void main()
{
	// Retro vertex manipulation:
	vec4 position = vec4(local_position, 1.0f);
	float amt = sin(position.x * 0.75 * (time * 0.2));

	// Back and forth:
	//float adjust = -(11.0f * sin(2 * PI * 0.25f * time + 1.0f) + 1.0f);
	
	if(position.y > adjust && position.y < adjust + line)
	{
		position.xy += amt * 0.25f;	
	}
	
	// Pulsing colors via normal pos:
	vec4 modNormal = normal * (sin(time) + 2.5f) / 2.0f;
	
	// Finalizing:
	gl_Position = (projection_view_matrix * model_matrix) * position;
	outNormal = modNormal * 2.5;
}