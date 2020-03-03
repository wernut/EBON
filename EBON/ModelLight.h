#pragma once
#include "PointLight.h"
#include "RawModel.h"

class ModelLight : public PointLight
{
private:
	RawModel* m_model;
public:

	ModelLight()
	{
		m_model = nullptr;
	}

	ModelLight(RawModel* model, glm::vec3 pos, float c, float l, float q, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient) 
		: PointLight(pos, c, l, q, diffuse, specular, ambient) 
	{
		m_model = model;
		m_model->setPosition(pos);
	}

	~ModelLight() 
	{
		if (m_model)
			delete m_model;
	}

	void setPos(glm::vec3 pos)
	{
		m_model->setPosition(pos);
		m_position = pos;
	}

	void render(Camera* camera)
	{
		m_model->render(camera);
	}

	RawModel* getModel()
	{
		return m_model;
	}
};