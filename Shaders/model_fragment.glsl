#version 450

// Phong lighting fragment shader:

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoords;
in vec3 vTangent;
in vec3 vBiTangent;

uniform vec3 camera_position;
uniform float specular_power = 32.0f;

layout(binding = 0) uniform sampler2D diffuseTexture;
layout(binding = 1) uniform sampler2D specularTexture;
layout(binding = 2) uniform sampler2D normalTexture;
layout(binding = 3) uniform sampler2D ambientTexture;
layout(binding = 4) uniform sampler2D glossTexture;

out vec4 final_color;

struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight;

struct PointLight 
{
	vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];	  

// Directional light function:
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    // Obtaining the rgb values of the textures at the specified coords:
    vec3 texDiffuse = texture(diffuseTexture, vTexCoords).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoords).rgb;
    vec3 texAmbient = texture(ambientTexture, vTexCoords).rgb;
    vec4 texGloss = texture(glossTexture, vTexCoords).rgba;		

	// Noramlizing the lights direction:
	vec3 lightDir = normalize(-light.direction);

	// Calculating lambert term for diffuse shading:
    float diff = max(dot(normal, lightDir), 0.0);

    // Calculating reflection for specular shading:
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specular_power);

    // Combining all results:
    vec3 ambient  = light.ambient  * texDiffuse;
    vec3 diffuse  = light.diffuse  * diff * texDiffuse;
    vec3 specular = light.specular * spec * texSpecular;
    return (ambient + diffuse + specular);
}

// Point light function:
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // Obtaining the rgb values of the textures at the specified coords:
    vec3 texDiffuse = texture(diffuseTexture, vTexCoords).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoords).rgb;
    vec3 texAmbient = texture(ambientTexture, vTexCoords).rgb;
    vec4 texGloss = texture(glossTexture, vTexCoords).rgba;		

    // Getting the light direction to the fragment:
    vec3 lightDir = normalize(light.position - fragPos);

    // Calculating lambert term for diffuse shading:
    float diff = max(dot(normal, lightDir), 0.0);

    // Calculating reflection for specular shading:
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specular_power);

    // Calculating attenuation to simulate drop off:
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    // Combining results:
    vec3 ambient  = light.ambient  * texDiffuse;
    vec3 diffuse  = light.diffuse  * diff * texDiffuse;
    vec3 specular = light.specular * spec * texSpecular;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

void main()
{
	// Normalizing all the passed values:
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);
	vec3 N = normalize(vNormal);
    vec3 texNormal = texture(normalTexture, vTexCoords).rgb;
	
	// Getting the TBN and setting the new normal:
	mat3 TBN = mat3(T,B,N);
	N = TBN * (texNormal * 2 - 1);

    // Getting the view direction to the fragment:
    vec3 viewDir = normalize(camera_position - vec3(vPosition));

    // Calculating the light:
	vec3 result = CalcDirLight(dirLight, N, viewDir);
    for(int i = 0; i < NR_POINT_LIGHTS; ++i)
    {
        result += CalcPointLight(pointLights[i], N, vec3(vPosition), viewDir);
    }
	
	// Assigning the final fragment colour:
	final_color = vec4(result, 1.0f);
}