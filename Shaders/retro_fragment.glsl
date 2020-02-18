#version 450

uniform vec4 color 	= vec4(1, 1, 1, 1);

out vec4 final_color;

in vec4 outNormal;

highp int x = int(gl_FragCoord.x);
highp int y = int(gl_FragCoord.y);
highp int z = int(gl_FragCoord.z);

int check = 3;

void main()
{	
	if(((x % check) == 0) && ((y % check) == 0) && ((z % check) == 0))
	{
		final_color = outNormal;	
	}
	else
	{
		final_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}
}