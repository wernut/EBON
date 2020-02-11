#pragma once
#include "ShaderProgram.h"
#include <string>

class ShaderProgram;

class ShaderManager
{
private:
	ShaderProgram** m_shaders;
	static ShaderManager* m_instance;

	ShaderManager();
	~ShaderManager();

public:

	// Singleton functions:
	static ShaderManager* Create()
	{
		if (!m_instance)
		{
			m_instance = new ShaderManager();
			return m_instance;
		}
		else
			return nullptr;
	}

	static void Destroy()
	{
		if (m_instance)
			delete m_instance;
	}

	static ShaderManager* getInstance() { return m_instance; }

	// 
	enum E_SHADER_TYPE
	{
		DEFAULT,
		COUNT,
	};

	ShaderProgram* getShader(E_SHADER_TYPE shaderType);
};

