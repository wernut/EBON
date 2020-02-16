#include "ShaderManager.h"

ShaderManager* ShaderManager::m_instance = nullptr;

ShaderManager::ShaderManager()
{
	m_shaders = new ShaderProgram *[COUNT];
	m_shaders[DEFAULT]  = new ShaderProgram("..\\Shaders\\simple_vertex.glsl",   "..\\Shaders\\simple_fragment.glsl");
	m_shaders[TEXTURED] = new ShaderProgram("..\\Shaders\\textured_vertex.glsl", "..\\Shaders\\textured_fragment.glsl");
	m_shaders[TERRAIN]	= new ShaderProgram("..\\Shaders\\terrain_vertex.glsl", "..\\Shaders\\terrain_fragment.glsl");
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
