/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       PointLight.h & PointLight.cpp
 * Purpose:     Serves as a point light, that sends light in each direction.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#pragma once
#include "DirectionalLight.h"

class PointLight : public DirectionalLight
{
protected:
	// Properties specific to the point light:
	glm::vec3 m_position;
	float m_constant;
	float m_linear;
	float m_quadratic;

public:
	/* Default constructor: */
	PointLight();

	/* Main constructor: 
		~ pos - Position of the light. 
		~ c - Constant value.
		~ l - Linear value.
		~ q - Quadratic value.
		~ dif - Diffuse property.
		~ spec - Specular property.
		~ amb - Ambient property.*/
	PointLight(glm::vec3 pos, float c, float l, float q, glm::vec3 dif, glm::vec3 spe, glm::vec3 amb);

	/* Destructor: */
	~PointLight();

	// Sets the position of the light in world space.
	void setPosition(glm::vec3 pos);

	// Sets the constant value of the light.
	void setConstant(float c);

	// Sets the linear value of the light.
	void setLinear(float l);

	// Sets the quadratic value of the light.
	void setQuadratic(float q);

	// Returns the position of the light in world space.
	glm::vec3 getPosition();

	// Returns the constant value of the light.
	float getConstant();

	// Returns the linear value of the light.
	float getLinear();

	// Returns the quadratic value of the light.
	float getQuadratic();
};
