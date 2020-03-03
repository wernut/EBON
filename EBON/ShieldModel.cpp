#include "ShieldModel.h"

ShieldModel::ShieldModel(aie::OBJMesh::MeshChunk chunk, DirectionalLight* dirLight, ModelLight** modelLights) : Model(new Mesh(chunk), dirLight, modelLights){}

ShieldModel::~ShieldModel() {}

void ShieldModel::update(float deltaTime) {}