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
#include "ShieldModel.h"

ShieldModel::ShieldModel(aie::OBJMesh::MeshChunk chunk, DirectionalLight* dirLight, ModelLight** modelLights) 
	: Model(new Mesh(chunk), dirLight, modelLights)
{
	addMap(E_DIFFUSE, "..\\Models\\SwordAndShield\\UVAlbedoMap_Shield.png", GL_RGBA);
	addMap(E_NORMAL, "..\\Models\\SwordAndShield\\UVNormalMap_Shield.png", GL_RGBA);
}

ShieldModel::~ShieldModel() {}

