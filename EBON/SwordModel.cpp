/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       DEMONSTRATION MODEL!
 * Purpose:     An object of a particular object, to demonstrate a lit model
 *              within a scene.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "SwordModel.h"

SwordModel::SwordModel(aie::OBJMesh::MeshChunk chunk, DirectionalLight* dirLight, ModelLight** modelLights)
	: Model(new Mesh(chunk), dirLight, modelLights)
{
	addMap(E_DIFFUSE, "..\\Models\\SwordAndShield\\UVAlbedoMap_Sword.png", GL_RGBA);
	addMap(E_NORMAL, "..\\Models\\SwordAndShield\\UVNormalMap_Sword.png", GL_RGBA);
}

SwordModel::~SwordModel() {}

