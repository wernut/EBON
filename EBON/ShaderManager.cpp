#include "ShaderManager.h"
#include "ShaderFade.h"
#include <iostream>

ShaderManager* ShaderManager::m_instance = nullptr;

ShaderManager::ShaderManager()
{
	m_shaders = new ShaderProgram *[COUNT];
	m_shaders[DEFAULT]     = new ShaderProgram("..\\Shaders\\default_vertex.glsl", "..\\Shaders\\default_fragment.glsl");
	m_shaders[DIR_LIT]     = new ShaderProgram("..\\Shaders\\dirlit_vertex.glsl",   "..\\Shaders\\dirlit_fragment.glsl");
	m_shaders[DIR_LIT_NM]  = new ShaderProgram("..\\Shaders\\dirlit_NM_vertex.glsl",   "..\\Shaders\\dirlit_NM_fragment.glsl");
	m_shaders[POI_LIT]	   = new ShaderProgram("..\\Shaders\\poilit_vertex.glsl", "..\\Shaders\\poilit_fragment.glsl");
	m_shaders[TRIPPY]      = new ShaderProgram("..\\Shaders\\Effects\\trippy_vertex.glsl", "..\\Shaders\\Effects\\trippy_fragment.glsl");
	m_shaders[RETRO]	   = new ShaderProgram("..\\Shaders\\Effects\\retro_vertex.glsl", "..\\Shaders\\Effects\\retro_fragment.glsl");
	m_shaders[FADE]		   = new ShaderFade();
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
	std::cout << "+ Recompiling active shaders... " << std::endl;
	for (int i = 0; i < COUNT; ++i)
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
