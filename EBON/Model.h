#pragma once
#include "TexturedModel.h"
#include "ModelLight.h"


class Model : public TexturedModel
{
private:
	DirectionalLight* m_dirLight;
	ModelLight** m_modelLights;
public:
	Model(Mesh* mesh, DirectionalLight* dirLight, ModelLight** modelLights);
	Model(const char* objLocation, DirectionalLight* dirLight, ModelLight** modelLights);
	~Model();

	virtual void update(float deltaTime);
	void render(Camera* camera);
};

