#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "..\glcore\gl_core_4_5.h"
#include <sstream>
#include <fstream>

using uint = unsigned int;

class ShaderProgram
{
private:
	uint m_vertexID;
	uint m_fragmentID;
	uint m_shaderProgramID;
	std::string m_vertexLocation, m_fragmentLocation;
	uint loadShader(const char* fileLocation, uint shaderType);
	GLint checkSuccess(uint id);
	void cleanUpShader();

public:
	ShaderProgram(std::string vertexLocation, std::string fragmentLocation);
	virtual ~ShaderProgram();

	uint getID();

	// Use the shader:
	void use();
	void bindAttributes();
	void stop();

	// Uniform functions:
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4(const std::string& name, glm::mat4 value) const;
	void setVector4(const std::string& name, glm::vec4 value) const;

	// Test function to reload the shader:
	bool Reload();
};

