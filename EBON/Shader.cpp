#include "Shader.h"
#include "..\glcore\gl_core_4_5.h"

// Set up the shader:
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	vertex_shader_ID = loadVertexShader(vertexPath);
	fragment_shader_ID = loadFragmentShader(fragmentPath);
	ID = linkShaders();
}

// Use the shader:
void Shader::use()
{
	glUseProgram(ID);
}

// Uniform functions:
void Shader::setBool(std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(std::string& name, int value) 
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(std::string& name, float value) 
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

uint Shader::loadVertexShader(const char* vertexPath)
{
	uint vertex_shader_ID = 0;
	std::string shader_data;
	std::ifstream in_file_stream("..\\Shaders\\simple_vertex.glsl", std::ifstream::in);

	// - Load source into string for compile:
	std::stringstream string_stream;
	if (in_file_stream.is_open())
	{
		string_stream << in_file_stream.rdbuf();
		shader_data = string_stream.str();
		in_file_stream.close();
	}

	// - Allocate space for shader program:
	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	// - Convert to raw char*:
	const char* data = shader_data.c_str();
	// - Send in the char* to shader location:
	glShaderSource(vertex_shader_ID, 1, (const GLchar**)&data, 0);
	// - Build!:
	glCompileShader(vertex_shader_ID);

	// - Check the shader compiled:
	GLint success = GL_FALSE;
	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// - Get length of OpenGL error message:
		GLint log_length = 0;
		glGetShaderiv(vertex_shader_ID, GL_INFO_LOG_LENGTH, &log_length);
		// - Create the error buffer: 
		char* log = new char[log_length];
		// - Copy the error from the buffer:
		glGetShaderInfoLog(vertex_shader_ID, log_length, 0, log);

		// - Create the error message:
		std::string error_message(log);
		error_message += "VETREX_SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());
		// - Clean up anyway:
		delete[] log;

		// Exiting the function after the error message:
		return -1;
	}

	return vertex_shader_ID;
}

uint Shader::loadFragmentShader(const char* fragmentPath)
{
	uint fragment_shader_ID = 0;
	std::string shader_data;
	std::ifstream in_file_stream_frag("..\\Shaders\\simple_fragment.glsl", std::ifstream::in);
	std::stringstream frag_string_stream;

	// - Load source into string for compile
	if (in_file_stream_frag.is_open())
	{
		frag_string_stream << in_file_stream_frag.rdbuf();
		shader_data = frag_string_stream.str();
		in_file_stream_frag.close();
	}

	// - Allocate space for shader program
	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	// - Convert to raw char*
	const char* data = shader_data.c_str();
	// - Send in the char* to shader location
	glShaderSource(fragment_shader_ID, 1, (const GLchar**)&data, 0);
	// - Build!
	glCompileShader(fragment_shader_ID);

	// - Did it work?
	// - Check the shader compiled
	GLint success = GL_FALSE;
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// - Get length of OpenGL error message:
		GLint log_length = 0;
		glGetShaderiv(fragment_shader_ID, GL_INFO_LOG_LENGTH, &log_length);
		// - Create the error buffer: 
		char* log = new char[log_length];
		// - Copy the error from the buffer:
		glGetShaderInfoLog(fragment_shader_ID, log_length, 0, log);

		// - Create the error message:
		std::string error_message(log);
		error_message += "FRAGMENT_SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());
		// - Clean up anyway:
		delete[] log;

		return -2;
	}
}

uint Shader::linkShaders()
{
	// - Creating the shader program.
	shader_program_ID = glCreateProgram();

	// - Attaching the vertex and fragment shader to the shader program.
	glAttachShader(shader_program_ID, vertex_shader_ID);
	glAttachShader(shader_program_ID, fragment_shader_ID);

	// - Linking the shaders:
	glLinkProgram(shader_program_ID);

	// - Checking for successful link:
	GLint success = GL_FALSE;
	glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		// - Get length of OpenGL error message:
		GLint log_length = 0;
		glGetShaderiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);
		// - Create the error buffer: 
		char* log = new char[log_length];
		// - Copy the error from the buffer:
		glGetShaderInfoLog(shader_program_ID, log_length, 0, log);

		// - Create the error message:
		std::string error_message(log);
		error_message += "SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());
		// - Clean up anyway:
		delete[] log;

		return -3;
	}

	glDeleteShader(vertex_shader_ID);
	glDeleteShader(fragment_shader_ID);

	return shader_program_ID;
}
