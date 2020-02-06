#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "glm.hpp"
#include "ext.hpp"

using uint = unsigned int;

class Shader
{
private:
	// Shader's ID:
	uint shader_program_ID;

	// Load and link the vertex and fragment shaders:
	void loadAndLinkShaders(const char* vertexPath, const char* fragmentPath);

public:
	// Set up the shader:
	Shader(const char* vertexPath, const char* fragmentPath);

	// Use the shader:
	void use();

	// Uniform functions:
	void setBool   (const std::string &name, bool value) const;
	void setInt    (const std::string &name, int value) const;
	void setFloat  (const std::string &name, float value) const;
	void setMatrix4(const std::string &name, glm::mat4 value) const;
	void setVector4(const std::string &name, glm::vec4 value) const;

	// Getter for the shaders ID.
	uint GetID();
};

