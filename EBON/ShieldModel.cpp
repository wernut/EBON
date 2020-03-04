#include "ShieldModel.h"

ShieldModel::ShieldModel(aie::OBJMesh::MeshChunk chunk, DirectionalLight* dirLight, ModelLight** modelLights) 
	: Model(new Mesh(chunk), dirLight, modelLights)
{
	addMap(E_DIFFUSE, "..\\Models\\SwordAndShield\\UVAlbedoMap_Shield.png", GL_RGBA);
	addMap(E_NORMAL, "..\\Models\\SwordAndShield\\UVNormalMap_Shield.png", GL_RGBA);
}

ShieldModel::~ShieldModel() {}

void ShieldModel::update(float deltaTime) {}