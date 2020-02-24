#version 450

in vec4 outNormal;
in float hasPassed;
in float isInLine;
in vec4 outLineColor;

out vec4 final_color;

void main()
{	
	if(isInLine == 1.0f)
	{

		final_color = outLineColor;
	}
	else if(hasPassed == 1.0f)
	{
		final_color = outNormal;	
	}
	else
	{
		// discard;
	}
}