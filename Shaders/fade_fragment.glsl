#version 450

in vec4 outNormal;
in float hasPassed;
in float isInLine;
out vec4 final_color;

in vec4 outLineColor;

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
		discard;
	}
}