#version 450

// Phong lighting fragment shader:

in vec4 outPosition;
in vec3 outNormal;
in vec2 outTexCoords;
in vec3 outTangent;
in vec3 outBiTangent;

uniform vec3 camera_position;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

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
	vec3 texDiffuse  = texture(diffuseTexture,  outTexCoords).rgb;
	vec3 texSpecular = texture(specularTexture, outTexCoords).rgb;
	vec3 texNormal   = texture(normalTexture,   outTexCoords).rgb;

	// Normalizing all the passed values:
	vec3 N = normalize(outNormal);
	vec3 T = normalize(outTangent);
	vec3 B = normalize(outBiTangent);
	vec3 L  = normalize(light_direction);
	
	// Getting the TBN and setting the new normal:
	mat3 TBN = mat3(T,B,N);
	N = TBN * (texNormal * 2 - 1);
	
	// Calculating the Lambert Term:
	float lambertTerm = max(0, dot(N, -L));
	
	// Calculating the view and reflection vectors:
	vec3 V = normalize(camera_position - outPosition.xyz);
	vec3 R = reflect(L, N);
	
	// Calculating the specular term:
	float specularTerm = pow(max(0, dot(R, V)), specular_power);
	
	// Calculating the final vectors:
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;
	vec3 specular = Is * Ks * texSpecular * specularTerm;
	
	// Assigning the final fragment colour:
	final_color = vec4(ambient + diffuse + specular, 1.0f);
}