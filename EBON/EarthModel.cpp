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
#include "EarthModel.h"
#include "Primitives.h"

EarthModel::EarthModel(DirectionalLight* dirLight, ModelLight** modelLights) : Model(Primitives::generateSphere(1.0f, 36.0f, 18.0f), dirLight, modelLights)
{
    // Adding image maps:
    addMap(E_DIFFUSE, "..\\Textures\\Earth\\earth_diffuse.jpg", GL_RGB);
    addMap(E_SPECULAR, "..\\Textures\\Earth\\earth_specular.jpg", GL_RGB);
    addMap(E_NORMAL, "..\\Textures\\Earth\\earth_normal.jpg", GL_RGB);
}

EarthModel::~EarthModel() {}

