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
#pragma once
#include "Model.h"
class ShieldModel : public Model
{
public:
	ShieldModel(aie::OBJMesh::MeshChunk chunk, DirectionalLight* dirLight, ModelLight** modelLights);
	~ShieldModel();

};

