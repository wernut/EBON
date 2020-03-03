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
	PointLight();
	PointLight(glm::vec3 pos, float c, float l, float q, glm::vec3 dif, glm::vec3 spe, glm::vec3 amb);
	~PointLight();

	glm::vec3 getPosition();
	float getConstant();
	float getLinear();
	float getQuadratic();
};
