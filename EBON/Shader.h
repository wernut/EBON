#pragma once
#include <string>
#include <fstream>
#include <sstream>

using uint = unsigned int;

class Shader
{
private:
	uint shader_program_ID;
	uint vertex_shader_ID;
	uint fragment_shader_ID;
	uint loadVertexShader(const char* vertexPath);
	uint loadFragmentShader(const char* fragmentPath);
	uint linkShaders();
public:
	// Shader's ID:
	uint ID;

	// Set up the shader:
	Shader(const char* vertexPath, const char* fragmentPath);

	// Use the shader:
	void use();

	// Uniform functions:
	void setBool(std::string &name, bool value);
	void setInt(std::string& name, int value);
	void setFloat(std::string& name, float value);
};

