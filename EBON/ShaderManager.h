#pragma once
#include "ShaderProgram.h"
#include <string>

class ShaderProgram;

class ShaderManager
{
private:
	ShaderProgram** m_shaders;
	static ShaderManager* m_instance;

public:
	ShaderManager();
	~ShaderManager();

	enum E_SHADER_TYPE
	{
		DEFAULT,
		TEXTURED,
		TRIPPY,
		RETRO,
		LIGHT,
		FADE,
		COUNT,
	};

	void ReloadAllShaders();

	ShaderProgram* getShader(E_SHADER_TYPE shaderType);
};

