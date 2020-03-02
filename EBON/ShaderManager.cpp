#include "ShaderManager.h"
#include "ShaderFade.h"
#include <iostream>

ShaderManager* ShaderManager::m_instance = nullptr;

ShaderManager::ShaderManager()
{
	m_shaders = new ShaderProgram *[E_COUNT];
	m_shaders[E_DEFAULT] = new ShaderProgram("..\\Shaders\\default_vertex.glsl", "..\\Shaders\\default_fragment.glsl");
	m_shaders[E_MODEL] = new ShaderProgram("..\\Shaders\\model_vertex.glsl",   "..\\Shaders\\model_fragment.glsl");
	m_shaders[E_FADE] = new ShaderFade();
}

ShaderManager::~ShaderManager()
{
	for (int i = 0; i < E_COUNT; ++i)
	{
		delete m_shaders[i];
		m_shaders[i] = 0;
	}
	delete m_shaders;
	m_shaders = nullptr;
}

ShaderProgram* ShaderManager::getShader(SHADER_TYPE shaderType)
{
	return m_shaders[shaderType];
}

void ShaderManager::ReloadAllShaders()
{
	std::cout << std::endl;
	std::cout << "+ Recompiling active shaders... " << std::endl;
	for (int i = 0; i < E_COUNT; ++i)
	{
		if (m_shaders[i]->GetInUse())
		{
			if (m_shaders[i]->Reload())
				std::cout << "ENUM_ID_" << i << "_SHADER_ID_" << m_shaders[i]->getID() << "_SUCCESS" << std::endl;
			else
				std::cout << "ENUM_ID_" << i << std::endl;
		}
	}
}
