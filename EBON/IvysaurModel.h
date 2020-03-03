#pragma once
#include "Model.h"
class IvysaurModel : public Model
{
public:
	IvysaurModel(DirectionalLight* dirLight, ModelLight** modelLights);
	~IvysaurModel();

	void update(float deltaTime);
};

