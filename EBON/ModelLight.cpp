#include "ModelLight.h"

ModelLight::ModelLight()
{
	m_model = nullptr;
}

ModelLight::ModelLight(RawModel* model, glm::vec3 pos, float c, float l, float q, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient)
	: PointLight(pos, c, l, q, diffuse, specular, ambient)
{
	m_model = model;
	m_model->addPosition(pos);
}

ModelLight::~ModelLight()
{
	if (m_model)
		delete m_model;
}

void ModelLight::setPos(glm::vec3 pos)
{
	m_model->addPosition(pos);
	m_position = pos;
}

void ModelLight::render(Camera* camera)
{
	m_model->render(camera);
}

RawModel* ModelLight::getModel()
{
	return m_model;
}