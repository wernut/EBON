/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       DirectionalLight.h & DirectionalLight.cpp
 * Purpose:     Represents a directional light in a scene. Also serves as a base
 *				class for now, will update and have a Light class in the future
 *				that does this.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#pragma once
#include "glm.hpp"

class DirectionalLight
{
private:
	// Direction of the light:
	glm::vec3 m_direction;

protected:
	// Light properties:
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_ambient;
public:
	/* Default constructor: */
	DirectionalLight();

	/* Main constructor:
		~ dir - Direction of the light.
		~ dif - Diffuse property.
		~ spe - Specular property.
		~ amb - Ambient property. */
	DirectionalLight(glm::vec3 dir, glm::vec3 dif, glm::vec3 spe, glm::vec3 amb);

	/* Destructor: */
	~DirectionalLight();

	// Sets the direction of the light.
	void setDirection(glm::vec3 dir);

	// Sets the diffuse property of the light.
	void setDiffuse(glm::vec3 diff);

	// Sets specular property of the light.
	void setSpecular(glm::vec3 spec);

	// Sets the ambient property of the light.
	void setAmbient(glm::vec3 amb);

	// Returns the direction.
	glm::vec3 getDirection();

	// Returns the diffuse property.
	glm::vec3 getDiffuse();

	// Returns the specular property.
	glm::vec3 getSpecular();

	// Returns the ambient property.
	glm::vec3 getAmbient();
};

