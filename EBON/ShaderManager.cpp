/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       ShaderManager.h & ShaderManager.cpp
 * Purpose:     Manages all initialised shaders.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "ShaderManager.h"
#include "ShaderFade.h"
#include <iostream>
#include <chrono>
#include <ctime>

ShaderManager::ShaderManager()
{
	// Initialising the array of shader programs:
	m_shaders = new ShaderProgram *[E_COUNT];
	m_shaders[E_DEFAULT] = new ShaderProgram("..\\Shaders\\default_vertex.glsl", "..\\Shaders\\default_fragment.glsl");
	m_shaders[E_MODEL] = new ShaderProgram("..\\Shaders\\model_vertex.glsl",   "..\\Shaders\\model_fragment.glsl");
	m_shaders[E_FADE] = new ShaderFade();
}

ShaderManager::~ShaderManager()
{
	// Deleting the array of shaders: 
	for (int i = 0; i < E_COUNT; ++i)
	{
		delete m_shaders[i];
		m_shaders[i] = 0;
	}
	delete[] m_shaders;
	m_shaders = nullptr;
}

ShaderProgram* ShaderManager::getShader(SHADER_TYPE shaderType)
{
	return m_shaders[shaderType];
}

void ShaderManager::ReloadActiveShaders()
{
	// Printing console message:
	std::cout << std::endl;
	std::cout << " + Recompiling active shaders... " << std::endl;

	// Looping through all shaders and checking if they're active and reloading them if they are.
	for (int i = 0; i < E_COUNT; ++i)
	{
		if (m_shaders[i]->GetActive())
		{
			if (m_shaders[i]->Reload())
				std::cout << "ENUM_ID_" << i << "_SHADER_ID_" << m_shaders[i]->getID() << "_SUCCESS" << std::endl;
			else
				std::cout << "ENUM_ID_" << i << std::endl;
		}
	}
}
