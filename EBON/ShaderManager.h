#pragma once
#include "ShaderProgram.h"
#include <string>

class ShaderProgram;

class ShaderManager
{
public:
	enum SHADER_TYPE
	{
		E_DEFAULT,
		E_MODEL,
		E_FADE,
		E_COUNT,
	};

	ShaderManager();
	~ShaderManager();

	void ReloadAllShaders();
	ShaderProgram* getShader(SHADER_TYPE shaderType);

private:
	ShaderProgram** m_shaders;
	static ShaderManager* m_instance;
};

