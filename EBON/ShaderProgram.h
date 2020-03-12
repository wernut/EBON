/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       ShaderProgram.h & ShaderProgram.cpp
 * Purpose:     Compiles and links a vertex and fragment shader.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "..\glcore\gl_core_4_5.h"
#include <sstream>
#include <fstream>

using uint = unsigned int;

class ShaderProgram
{
public:
	/* Main Constructor - Loads and links vertex and frament shader: 
		~ std::string vertexLocation - Vertex Shader location.
		~ std::string fragmentLocation - Fragment shader location. */
	ShaderProgram(std::string vertexLocation, std::string fragmentLocation);

	/* Virtual destructor: */
	virtual ~ShaderProgram();

	// Virtual functions for derived classes:
	//--
	virtual void Update(float deltaTime);
	virtual void ToggleEffect(float args0 = 0.0f, float args1 = 0.0f, float args2 = 0.0f);
	virtual void StartEffect();
	virtual void StopEffect();
	virtual void ResetEffect();
	//--

	// Get the shader ID:
	uint getID();

	// Use the shader:
	void bind();

	// Stop using the shader:
	void unbind();

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

	// Sets the shaders active status:
	void SetActive(bool value);

	// Returns the shaders active status:
	bool GetActive();

	// Returns the effect status of the shader:
	bool GetEffectStatus();

private:
	// Location of vertex fragment on the GPU.
	uint m_vertexID;

	// Location of fragment shader on the GPU.
	uint m_fragmentID;

	// Location of linked shaders on the GPU.
	uint m_shaderProgramID;

	// Location of vertex and fragment shader on the drive:
	std::string m_vertexLocation, m_fragmentLocation;

	/* Function to load and compile either a vertex or fragment shader: 
		~ const char* fileLocation - The location of the shader on the computer.
		~ GLint shaderType - The type of shader we want to load. */
	uint loadShader(const char* fileLocation, GLint shaderType);

	/* Function to check if the shader compiled:
		~ GLint id - The ID of the shader we want to check.*/
	GLint checkSuccess(GLint id);

	// Deattaches the shaders from the program and deletes them all.
	void cleanUpShader();

protected:
	// Effect status of the shader.
	bool m_effectStatus;

	// Active flag for reloading purposes. (Is the shader being used?)
	bool m_isActive;
};

