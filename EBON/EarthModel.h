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
class EarthModel : public Model
{
public:
	EarthModel(DirectionalLight* dirLight, ModelLight** modelLights);
	~EarthModel();
};

