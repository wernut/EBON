#pragma once
#include "PointLight.h"
#include "RawModel.h"

class ModelLight : public PointLight
{
private:
	RawModel* m_model;
public:

	ModelLight();
	ModelLight(RawModel* model, glm::vec3 pos, float c, float l, float q,
		glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient);
	~ModelLight();

	void setPos(glm::vec3 pos);
	void render(Camera* camera);
	RawModel* getModel();
};