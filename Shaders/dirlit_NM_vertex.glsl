#version 450

// Phong lighting vertex shader:

layout(location = 0) in vec4 local_position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 tex_coords;
layout(location = 3) in vec4 tangent;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

out vec4 outPosition;
out vec3 outNormal;
out vec2 outTexCoords;
out vec3 outTangent;
out vec3 outBiTangent;

void main()
{
	outPosition = model_matrix * local_position;
	outNormal = normal_matrix * normal.xyz;
	outTexCoords = tex_coords;
	outTangent = normal_matrix * tangent.xyz;
	outBiTangent = cross(outNormal, outTangent) * tangent.w;
	gl_Position = (projection_view_matrix * model_matrix) * local_position;
}