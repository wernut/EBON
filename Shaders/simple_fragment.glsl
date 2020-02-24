#version 450

out vec4 final_color;

in vec3 outNormal;
in vec4 outPosition;
in vec2 outTexCoords;

// texture sampler
uniform sampler2D diffuseTexture;

uniform vec3 Ia; // ambient light colour
uniform vec3 Id; // diffuse light colour
uniform vec3 Is; // specular light colour
uniform vec3 light_direction;

uniform vec3 Ka = vec3(1.0f, 1.0f, 1.0f); // ambient material colour
uniform vec3 Kd = vec3(1.0f, 1.0f, 1.0f); // diffuse material colour
uniform vec3 Ks = vec3(1.0f, 1.0f, 1.0f); // specular material colour
uniform float specularPower = 0.5f;

uniform vec3 camera_position;

void main()
{

	// normalizing the normals and light direction
	vec3 N = normalize(outNormal);
	vec3 L  = normalize(light_direction);
	
	// calculating lambert term
	float lambertTerm = max(0, min(1, dot(N, -L)));
	
	// calculate view vector and reflection vector
	vec3 V = normalize(camera_position - outPosition.xyz);
	vec3 R = reflect(L, N);
	
	// calculate specular term
	float specularTerm = pow(max(0, dot(R, V)), specularPower);
	
	// calculate each colour property
	vec3 ambient = Ia * Ka;
	vec3 diffuse = Id * Kd * lambertTerm;
	vec3 specular = Is * Ks * specularTerm;
	
	// result
	final_color = vec4(ambient + diffuse + specular, 1.0f) * texture(diffuseTexture, outTexCoords);
}