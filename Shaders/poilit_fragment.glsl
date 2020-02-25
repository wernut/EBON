#version 450

uniform sampler2D ourTexture;
uniform vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 lightPos = vec4(0.0f, 0.0f, 0.0f, 1.0f);
uniform vec3 viewPos = vec3(0.0f, 0.0f, 0.0f);

in vec4 outPosition;
in vec4 outNormal;
in vec2 outTexCoords;

out vec4 final_color;

void main()
{
	// Calculate ambient light:
	float ambientStrength = 0.1f;
	vec4 ambient = ambientStrength * lightColor;
	
	// Normalise normals and and obtain light direction:
	vec4 N = normalize(outNormal);
	vec4 L = normalize(lightPos - outPosition);
	
	// Calculate lambert function:
	float lambertTerm = max(0, min(1, dot(N, -L)));
	vec4 diffuse = lambertTerm * lightColor;

	float specularStrength = 0.5f;
	vec4 V = normalize(vec4(viewPos, 1.0f) - outPosition);
	vec4 R = reflect(-L, N);

	float specularTerm = pow(max(0, dot(R, V)), 32);
	vec4 specular = specularStrength * specularTerm * lightColor;

	vec4 result = (ambient + diffuse + specular) * texture(ourTexture, outTexCoords);

	final_color = result;
}