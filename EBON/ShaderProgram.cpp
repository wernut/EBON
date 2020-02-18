#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string vertexLocation, std::string fragmentLocation)
{
	// Storing the location of the files:
	m_vertexLocation = vertexLocation;
	m_fragmentLocation = fragmentLocation;

	// Loading the vertex and fragment shader:
	m_vertexID   = loadShader(vertexLocation.c_str(),   GL_VERTEX_SHADER);
	m_fragmentID = loadShader(fragmentLocation.c_str(), GL_FRAGMENT_SHADER);

	// - Creating the shader program:
	m_shaderProgramID = glCreateProgram();

	// - Attaching the vertex and fragment shader to the shader program:
	glAttachShader(m_shaderProgramID, m_vertexID);
	glAttachShader(m_shaderProgramID, m_fragmentID);

	// - Linking the shaders:
	glLinkProgram(m_shaderProgramID);
}

ShaderProgram::~ShaderProgram()
{
	cleanUpShader();
}

uint ShaderProgram::loadShader(const char* fileLocation, uint shaderType)
{
	// Loading vertex shader:
	uint id = 0;
	std::string shader_data;
	std::ifstream in_file_stream(fileLocation, std::ifstream::in);

	// - Load source into string for compile:
	std::stringstream string_stream;
	if (in_file_stream.is_open())
	{
		string_stream << in_file_stream.rdbuf();
		shader_data = string_stream.str();
		in_file_stream.close();
	}

	// - Allocate space for shader program:
	id = glCreateShader(shaderType);
	// - Convert to raw char*:
	const char* data = shader_data.c_str();
	// - Send in the char* to shader location:
	glShaderSource(id, 1, (const GLchar**)&data, 0);
	// - Build!:
	glCompileShader(id);

	// - Check the shader compiled:
	return checkSuccess(id);
}

uint ShaderProgram::getID()
{
	return m_shaderProgramID;
}

GLint ShaderProgram::checkSuccess(uint id)
{
	// - Check the shader compiled:
	GLint success = GL_FALSE;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// - Get length of OpenGL error message:
		GLint log_length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
		// - Create the error buffer: 
		char* log = new char[log_length];
		// - Copy the error from the buffer:
		glGetShaderInfoLog(id, log_length, 0, log);

		// - Create the error message:
		std::string error_message(log);
		error_message += "_SHADER_FAILED_TO_COMPILE_";
		printf(error_message.c_str());
		// - Clean up anyway:
		delete[] log;

		return -1;
	}

	return id;
}

// Use the shader:
void ShaderProgram::use()
{
	glUseProgram(m_shaderProgramID);
}

// Bind the attributes:
void ShaderProgram::bindAttributes() {}

// Stop using the shader:
void ShaderProgram::stop()
{
	glUseProgram(0);
}
 
// Uniform functions:
void ShaderProgram::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgramID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgramID, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_shaderProgramID, name.c_str()), value);
}

void ShaderProgram::setMatrix4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramID, name.c_str()), 1, false, glm::value_ptr(value));
}

void ShaderProgram::setVector4(const std::string& name, glm::vec4 value) const
{
	glUniform4fv(glGetUniformLocation(m_shaderProgramID, name.c_str()), 1, glm::value_ptr(value));
}

// Function to recompile the shader at runtime:
bool ShaderProgram::Reload()
{
	// - Deattach and delete shaders:
	cleanUpShader();

	// - Loading the vertex and fragment shader:
	m_vertexID   = loadShader(m_vertexLocation.c_str(), GL_VERTEX_SHADER);
	m_fragmentID = loadShader(m_fragmentLocation.c_str(), GL_FRAGMENT_SHADER);

	// - If either of the shaders fail to compile, then exit out of the function.
	if (m_vertexID == -1 || m_fragmentID == -1)
	{
		cleanUpShader();
		return false;
	}

	// - Creating the shader program:
	m_shaderProgramID = glCreateProgram();

	// - Attaching the vertex and fragment shader to the shader program:
	glAttachShader(m_shaderProgramID, m_vertexID);
	glAttachShader(m_shaderProgramID, m_fragmentID);

	// - Linking the shaders:
	glLinkProgram(m_shaderProgramID);

	// - Successfully loaded shader:
	return true;
}

void ShaderProgram::cleanUpShader()
{
	glDetachShader(m_shaderProgramID, m_vertexID);
	glDetachShader(m_shaderProgramID, m_fragmentID);
	glDeleteShader(m_vertexID);
	glDeleteShader(m_fragmentID);
	glDeleteProgram(m_shaderProgramID);
}
