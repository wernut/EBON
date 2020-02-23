#version 450

layout(location = 0) in vec3 local_position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 tex_coords;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;

out vec4 outFragPos;
out vec4 outNormal;
out vec2 outTexCoords;


void main()
{
	vec4 position = vec4(local_position, 1.0f);

	outFragPos = vec4(model_matrix * position);
	outNormal = normal;
	outTexCoords = tex_coords;

	gl_Position = (projection_view_matrix * model_matrix) * position;
}