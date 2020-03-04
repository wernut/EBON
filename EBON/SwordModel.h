#pragma once
#include "Model.h"

class SwordModel : public Model
{
public:
	SwordModel(aie::OBJMesh::MeshChunk chunk, DirectionalLight* dirLight, ModelLight** modelLights);
	~SwordModel();

	void update(float deltaTime);
};

