#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	// Initialising the properties to 0.
	m_direction = glm::vec3(0.0f);
	m_diffuse = glm::vec3(0.0f);
	m_specular = glm::vec3(0.0f);
	m_ambient = glm::vec3(0.0f);
}

DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 dif, glm::vec3 spe, glm::vec3 amb)
{
	// Initialising the properties to the passed values:
	m_direction = dir;
	m_diffuse = dif;
	m_specular = spe;
	m_ambient = amb;
}

DirectionalLight::~DirectionalLight() {}

void DirectionalLight::setDirection(glm::vec3 dir)
{
	m_direction = dir;
}

void DirectionalLight::setDiffuse(glm::vec3 diff)
{
	m_diffuse = diff;
}

void DirectionalLight::setSpecular(glm::vec3 spec)
{
	m_specular = spec;
}

void DirectionalLight::setAmbient(glm::vec3 amb)
{
	m_ambient = amb;
}

glm::vec3 DirectionalLight::getDirection()
{
	return m_direction;
}

glm::vec3 DirectionalLight::getDiffuse()
{
	return m_diffuse;
}

glm::vec3 DirectionalLight::getSpecular()
{
	return m_specular;
}

glm::vec3 DirectionalLight::getAmbient()
{
	return m_ambient;
}