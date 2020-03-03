#pragma once
#include "Model.h"
class EarthModel : public Model
{
public:
	EarthModel(DirectionalLight* dirLight, ModelLight** modelLights);
	~EarthModel();

	void update(float deltaTime);
};

