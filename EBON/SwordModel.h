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

class SwordModel : public Model
{
public:
	SwordModel(aie::OBJMesh::MeshChunk chunk, DirectionalLight* dirLight, ModelLight** modelLights);
	~SwordModel();

};

