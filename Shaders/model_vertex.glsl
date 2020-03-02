#version 450

// Phong lighting vertex shader:

layout(location = 0) in vec4 local_position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 tex_coords;
layout(location = 3) in vec4 tangent;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

out vec4 vPosition;
out vec3 vNormal;
out vec2 vTexCoords;
out vec3 vTangent;
out vec3 vBiTangent;

void main()
{
	vPosition = model_matrix * local_position;
	vNormal = normal_matrix * normal.xyz;
	vTexCoords = tex_coords;
	vTangent = normal_matrix * tangent.xyz;
	vBiTangent = cross(vNormal, vTangent) * tangent.w;
	gl_Position = (projection_view_matrix * model_matrix) * local_position;
}