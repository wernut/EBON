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

protected:
	bool m_bEffectStatus;
	bool m_bIsInUse;

public:
	ShaderProgram(std::string vertexLocation, std::string fragmentLocation);

	// virutal functions:
	virtual ~ShaderProgram();
	virtual void update(float deltaTime);
	virtual void toggleEffect(float args0 = 0.0f, float args1 = 0.0f, float args2 = 0.0f);
	virtual void startEffect();
	virtual void stopEffect();
	virtual void resetEffect();

	// Get the shader ID:
	uint getID();

	// Use the shader:
	void use();
	void stop();

	// Uniform functions:
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4(const std::string& name, glm::mat4 value) const;
	void setMatrix3(const std::string& name, glm::mat3 value) const;
	void setVector4(const std::string& name, glm::vec4 value) const;
	void setVector3(const std::string& name, glm::vec3 value) const;

	// Function to reload the shader:
	bool Reload();
	void SetInUse(bool value);
	bool GetInUse();
	bool GetEffectStatus();
};

