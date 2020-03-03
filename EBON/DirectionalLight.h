#pragma once
#include "glm.hpp"

class DirectionalLight
{
private:
	glm::vec3 m_direction;

protected:
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_ambient;
public:
	DirectionalLight()
	{
		m_direction = glm::vec3(0.0f);
		m_diffuse = glm::vec3(0.0f);
		m_specular = glm::vec3(0.0f);
		m_ambient = glm::vec3(0.0f);
	}

	DirectionalLight(glm::vec3 dir, glm::vec3 dif, glm::vec3 spe, glm::vec3 amb)
	{
		m_direction = dir;
		m_diffuse = dif;
		m_specular = spe;
		m_ambient = amb;
	}

	~DirectionalLight(){}

	glm::vec3 getDirection()
	{
		return m_direction;
	}

	glm::vec3 getDiffuse()
	{
		return m_diffuse;
	}

	glm::vec3 getSpecular()
	{
		return m_specular;
	}

	glm::vec3 getAmbient()
	{
		return m_ambient;
	}
};

