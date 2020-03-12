/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       ShaderManager.h & ShaderManager.cpp
 * Purpose:     Manages all initialised shaders.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#pragma once
#include "ShaderProgram.h"
#include <string>

class ShaderProgram;

class ShaderManager
{
public:
	// Enum to hold all the initialised shaders:
	enum SHADER_TYPE
	{
		E_DEFAULT,
		E_MODEL,
		E_FADE,
		E_COUNT,
	};

	/* Default/Main Consturctor: */
	ShaderManager();

	/* Destructor: */
	~ShaderManager();

	// Reloads all active shaders:
	void ReloadActiveShaders();

	// Returns a shader via the shaderType enum:
	ShaderProgram* getShader(SHADER_TYPE shaderType);

private:
	// Array of initialised shaders:
	ShaderProgram** m_shaders;
};

