#include "ShaderManager.h"
#include <iostream>

ShaderManager* ShaderManager::m_instance = nullptr;

ShaderManager::ShaderManager()
{
	m_shaders = new ShaderProgram *[COUNT];
	m_shaders[DEFAULT]  = new ShaderProgram("..\\Shaders\\simple_vertex.glsl",   "..\\Shaders\\simple_fragment.glsl");
	m_shaders[TEXTURED] = new ShaderProgram("..\\Shaders\\textured_vertex.glsl", "..\\Shaders\\textured_fragment.glsl");
	m_shaders[TRIPPY] = new ShaderProgram("..\\Shaders\\trippy_vertex.glsl", "..\\Shaders\\trippy_fragment.glsl");
	m_shaders[RETRO] = new ShaderProgram("..\\Shaders\\retro_vertex.glsl", "..\\Shaders\\retro_fragment.glsl");
}

ShaderManager::~ShaderManager()
{
	for (int i = 0; i < COUNT; ++i)
	{
		delete m_shaders[i];
		m_shaders[i] = 0;
	}
	delete m_shaders;
	m_shaders = nullptr;
}

ShaderProgram* ShaderManager::getShader(E_SHADER_TYPE shaderType)
{
	return m_shaders[shaderType];
}

void ShaderManager::ReloadAllShaders()
{
	std::cout << std::endl;
	std::cout << "+ Reloading shaders... " << std::endl;
	for (int i = 0; i < COUNT; ++i)
	{
		if (m_shaders[i]->Reload())
			std::cout << "ID_" << m_shaders[i]->getID() << "_SUCCESS" << std::endl;
		else
			std::cout << "ID_" << m_shaders[i]->getID() << std::endl;

	}
}
