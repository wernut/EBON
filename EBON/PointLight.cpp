/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       PointLight.h & PointLight.cpp
 * Purpose:     Serves as a point light, that sends light in each direction.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "PointLight.h"

PointLight::PointLight()
{
	// Initialising the properties to 0.
	m_position = glm::vec3(0.0f);
	m_constant = 0.0f;
	m_linear = 0.0f;
	m_quadratic = 0.0f;
}

PointLight::PointLight(glm::vec3 pos, float c, float l, float q, glm::vec3 dif, glm::vec3 spe, glm::vec3 amb) : DirectionalLight(glm::vec3(0.0f), dif, spe, amb)
{
	// Initialising the values to the passed paramenters.
	m_position = pos;
	m_constant = c;
	m_linear = l;
	m_quadratic = q;
	m_diffuse = dif;
	m_specular = spe;
	m_ambient = amb;
}

PointLight::~PointLight() {}

void PointLight::setPosition(glm::vec3 pos)
{
	m_position = pos;
}

void PointLight::setConstant(float c)
{
	m_constant = c;
}

void PointLight::setLinear(float l)
{
	m_linear = l;
}

void PointLight::setQuadratic(float q)
{
	m_quadratic = q;
}

glm::vec3 PointLight::getPosition()
{
	return m_position;
}

float PointLight::getConstant()
{
	return m_constant;
}

float PointLight::getLinear()
{
	return m_linear;
}

float PointLight::getQuadratic()
{
	return m_quadratic;
}