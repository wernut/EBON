#version 450

layout(location = 0) in vec3 local_position;
layout(location = 1) in vec4 normal;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform float time;

out vec4 outNormal;

void main()
{
	vec4 position = vec4(local_position, 1.0f);
	float amt = (1.0f * 0.5f * sin(local_position.x * 50 * (time * 0.03f)) * 0.2f) + 1.0f;
	vec4 dist = vec4(normal) *  ((sin(time) + 2.0f) / 2.0f) * 3.5f;
	
	position = position + amt * dist;
	
	gl_Position = (projection_view_matrix * model_matrix) * position;
	
	vec4 modNormal = normal * (sin(time) + 2.5f) / 2.0f;
	
	outNormal = modNormal;
}