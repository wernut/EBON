#pragma once
#include "DirectionalLight.h"

class PointLight : public DirectionalLight
{
protected:
	glm::vec3 m_position;
	float m_constant;
	float m_linear;
	float m_quadratic;

public:
	PointLight()
	{
		m_position = glm::vec3(0.0f);
		m_constant = 0.0f;
		m_linear = 0.0f;
		m_quadratic = 0.0f;
	}

	PointLight(glm::vec3 pos, float c, float l, float q, glm::vec3 dif, glm::vec3 spe, glm::vec3 amb) : DirectionalLight(glm::vec3(0.0f), dif, spe, amb)
	{
		m_position = pos;
		m_constant = c;
		m_linear = l;
		m_quadratic = q;
		m_diffuse = dif;
		m_specular = spe;
		m_ambient = amb;
	}

	~PointLight() {}

	glm::vec3 getPosition()
	{
		return m_position;
	}

	float getConstant()
	{
		return m_constant;
	}

	float getLinear()
	{
		return m_linear;
	}

	float getQuadratic()
	{
		return m_quadratic;
	}
};
