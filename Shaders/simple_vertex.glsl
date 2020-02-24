#version 450

layout(location = 0) in vec3 local_position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 tex_coords;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

out vec4 outPosition;
out vec3 outNormal;
out vec2 outTexCoords;

void main()
{
	outPosition = model_matrix * vec4(local_position, 1.0f);
	outNormal = normal_matrix * normal.xyz;
	outTexCoords = tex_coords;
	gl_Position = (projection_view_matrix * model_matrix) * vec4(local_position, 1.0f);
}