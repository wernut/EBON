#include "SwordModel.h"

SwordModel::SwordModel(aie::OBJMesh::MeshChunk chunk, DirectionalLight* dirLight, ModelLight** modelLights)
	: Model(new Mesh(chunk), dirLight, modelLights)
{
	addMap(E_DIFFUSE, "..\\Models\\SwordAndShield\\UVAlbedoMap_Sword.png", GL_RGBA);
	addMap(E_NORMAL, "..\\Models\\SwordAndShield\\UVNormalMap_Sword.png", GL_RGBA);
}

SwordModel::~SwordModel() {}

void SwordModel::update(float deltaTime) {}