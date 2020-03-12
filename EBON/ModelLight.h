/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       ModelLight.h & ModelLight.cpp
 * Purpose:     Serves as a light which is has a model attached to it.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/

#pragma once
#include "PointLight.h"
#include "RawModel.h"

class ModelLight : public PointLight
{
private:
	// Model the class will use to represent the light.
	RawModel* m_model;
public:

	/* Default constructor: */
	ModelLight();

	/* Main constructor: 
		~ model - The raw model the class will use to represent the light. 
		~ pos - The position of the model and light. 
		~ c - The constant value of the light.
		~ l - The linear value of the light.
		~ q - The quadratic value of the light.
		~ diffuse - The diffuse property of the light. 
		~ specular - The specular property of the light.
		~ ambient - The ambient property of the light. */
	ModelLight(RawModel* model, glm::vec3 pos, float c, float l, float q,
		glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient);

	/* Destructor: */
	~ModelLight();

	// Sets the position of both light and model.
	void setPos(glm::vec3 pos);

	// Renders the model. 
	void Render(Camera* camera);

	// Returns the model.
	RawModel* getModel();
};