#version 450

uniform vec4 objectColor;
uniform vec4 lightColor;
uniform vec4 lightPos;
uniform vec3 viewPos;

out vec4 final_color;

in vec4 outNormal;
in vec4 outFragPos;

void main()
{
	// Phong lighting:
	float ambientStrength = 0.1f;
	vec4 ambient = ambientStrength * lightColor;

	vec4 norm = normalize(outNormal);
	vec4 lightDir = normalize(lightPos - outFragPos);

	float diff = max(dot(norm, lightDir), 0.0f);
	vec4 diffuse = diff * lightColor;

	float specularStrength = 0.5f;
	vec4 viewDir = normalize(vec4(viewPos, 1.0f) - outFragPos);
	vec4 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec4 specular = specularStrength * spec * lightColor;

	vec4 result = (ambient + diffuse + specular) * objectColor;
	final_color = result;
}