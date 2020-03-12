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
#include "IvysaurModel.h"

IvysaurModel::IvysaurModel(DirectionalLight* dirLight, ModelLight** modelLights) : Model("..\\Models\\Ivysaur\\Pokemon.obj", dirLight, modelLights)
{
    // Adding image maps:
    addMap(E_DIFFUSE, "..\\Textures\\Ivysaur\\Final_Pokemon_Diffuse.png", GL_RGBA);
    addMap(E_SPECULAR, "..\\Textures\\Ivysaur\\Final_Pokemon_Specular.png", GL_RGBA);
    addMap(E_NORMAL, "..\\Textures\\Ivysaur\\Final_Pokemon_Normal.png", GL_RGBA);
    addMap(E_AMBIENT, "..\\Textures\\Ivysaur\\Final_Pokemon_Ambient_Occlusion.png", GL_RGBA);
    addMap(E_GLOSS, "..\\Textures\\Ivysaur\\Final_Pokemon_Glossiness.png", GL_RGBA);
}

IvysaurModel::~IvysaurModel(){}

