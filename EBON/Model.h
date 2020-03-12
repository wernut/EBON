/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       Model.h & Model.cpp
 * Purpose:     To light model within a scene.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/

#pragma once
#include "TexturedModel.h"
#include "ModelLight.h"


class Model : public TexturedModel
{
public:
	/* Default constructor: */
	Model();

	/* Mesh* constructor:
		~ Mesh* mesh - The mesh object the RawModel base class will use.
		~ DirectionalLight* dirLight - Directional light the model will use to be lit.
		~ ModelLight** modelLights - Array of ModelLights the model will use to be lit. */
	Model(Mesh* mesh, DirectionalLight* dirLight, ModelLight** modelLights);

	/* Mesh* constructor:
		~ const char* objLocation - The location of the OBJ mesh that will be passed to the RawModel.
		~ DirectionalLight* dirLight - Directional light the model will use to be lit.
		~ ModelLight** modelLights - Array of ModelLights the model will use to be lit. */
	Model(const char* objLocation, DirectionalLight* dirLight, ModelLight** modelLights);

	/* Virtual destructor: */
	virtual ~Model();

	/* Applies the light properties to the shader and renders the textured model:
		~ Camera* camera - Camera object that was created for rendering. */
	void Render(Camera* camera);

private:
	// Pointers to the Directional and Model lights:
	DirectionalLight* m_dirLight;
	ModelLight** m_modelLights;
};

