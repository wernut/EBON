#version 450

// Phong lighting fragment shader:

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;
in vec3 vTangent;
in vec3 vBiTangent;

uniform vec3 camera_position;

layout(binding = 0) uniform sampler2D diffuseTexture;
layout(binding = 1) uniform sampler2D specularTexture;
layout(binding = 2) uniform sampler2D normalTexture;
layout(binding = 3) uniform sampler2D ambientTexture;
layout(binding = 4) uniform sampler2D glossTexture;

uniform vec3 Ka = vec3(0.25f, 0.25f, 0.25f);// mat ambient colour					
uniform vec3 Kd = vec3(1.0f, 1.0f, 1.0f); // mat diffuse colour
uniform vec3 Ks = vec3(1.0f, 1.0f, 1.0f); // mat spec colour						  
uniform float specular_power = 32.0f;

uniform vec3 Ia; 						  	// ambient light colour
uniform vec3 Id; 						  	// diffuse light colour
uniform vec3 Is;						  	// specular light colour
uniform vec3 light_direction;

out vec4 final_color;

void main()
{
	// Obtaining the rgb values of the textures at the specified coords:
	vec3 texDiffuse = texture(diffuseTexture, vTexCoords).rgb;
	vec3 texSpecular = texture(specularTexture, vTexCoords).rgb;
	vec3 texNormal = texture(normalTexture, vTexCoords).rgb;
	vec3 texAmbient = texture(ambientTexture, vTexCoords).rgb;
	vec4 texGloss = texture(glossTexture, vTexCoords).rgba;

	// Normalizing all the passed values:
	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	vec3 L  = normalize(light_direction);
	
	// Getting the TBN and setting the new normal:
	mat3 TBN = mat3(T,B,N);
	N = TBN * (texNormal * 2 - 1);
	
	// Calculating the Lambert Term:
	float lambertTerm = max(0, dot(N, -L));
	
	// Calculating the view and reflection vectors:
	vec3 V = normalize(camera_position - vPosition.xyz);
	vec3 R = reflect(L, N);
	
	// Calculating the specular term:
	float specularTerm = pow(max(0, dot(R, V)), specular_power);
	if(texGloss.a >= 0)
	{
		//specularTerm * texGloss.a;
	}
	
	// Calculating the final vectors:
	vec3 ambient = Ia * Ka;
	if(texAmbient.r > 0)
	{
		//ambient * texAmbient;
	}
	vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	vec3 specular = Is * Ks * texSpecular * specularTerm;
	
	// Assigning the final fragment colour:
	final_color = vec4(ambient + diffuse + specular, 1.0f);
}