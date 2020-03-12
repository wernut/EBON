/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       ModelLight.h & ModelLight.cpp
 * Purpose:     Serves as a light which is has a model attached to it.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "ModelLight.h"

ModelLight::ModelLight()
{
	m_model = nullptr;
}

ModelLight::ModelLight(RawModel* model, glm::vec3 pos, float c, float l, float q, 
					  glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient)
					 : PointLight(pos, c, l, q, diffuse, specular, ambient)
{
	// Sending all light values to the PointLight base class.

	// Initialising the model with the pass model, then setting it's pos.
	m_model = model;
	m_model->addPosition(pos);
}

ModelLight::~ModelLight()
{
	// Clean up model if exists:
	if (m_model)
		delete m_model;
}

void ModelLight::setPos(glm::vec3 pos)
{
	// Setting the model pos:
	m_model->addPosition(pos);

	// Setting the light pos:
	m_position = pos;
}

void ModelLight::Render(Camera* camera)
{
	// Rendering the model:
	m_model->Render(camera);
}

RawModel* ModelLight::getModel()
{
	return m_model;
}