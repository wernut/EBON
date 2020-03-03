#pragma once
#include "Model.h"
class ShieldModel : public Model
{
public:
	ShieldModel(aie::OBJMesh::MeshChunk chunk, DirectionalLight* dirLight, ModelLight** modelLights);
	~ShieldModel();

	void update(float deltaTime);
};

