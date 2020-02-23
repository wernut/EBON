#version 450

#define PI 3.1415926535897932384626433832795

layout(location = 0) in vec3 local_position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec4 tex_coords;

uniform mat4 projection_view_matrix;
uniform mat4 model_matrix;
uniform float appTime;
uniform float timer;
uniform bool isRunning;
uniform bool hasFaded;
uniform vec4 lineColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

out vec4 outNormal;
out vec4 outLineColor;
out float hasPassed;
out float isInLine;

float line = 0.25f;

void main()
{
	vec4 position = vec4(local_position, 1.0f);

	outLineColor = lineColor;

	if(isRunning)
	{

		if(position.y > timer && position.y < timer + line)
		{
			isInLine = 1.0f;
		}

		if(position.y > timer)
		{
			hasPassed = 1.0f;
		}	
	}
	else
	{
		isInLine = -1.0f;

		if(timer > line && position.y > timer && position.y < timer + line)
		{
			isInLine = 1.0f;
		}

		if(position.y > timer)
		{
			hasPassed = 1.0f;
		}
	}
	
	// Finalizing:
	gl_Position = (projection_view_matrix * model_matrix) * position;
	outNormal = normal;
}