#version 450

uniform sampler2D ourTexture;
uniform vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 lightPos = vec4(0.0f, 0.0f, 0.0f, 1.0f);
uniform vec3 viewPos = vec3(0.0f, 0.0f, 0.0f);

in vec4 outFragPos;
in vec4 outNormal;
in vec2 outTexCoords;

out vec4 final_color;

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

	vec4 result = (ambient + diffuse + specular) * texture(ourTexture, outTexCoords);

	final_color = result;
}