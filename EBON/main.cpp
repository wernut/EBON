#include "glm.hpp"
#include "ext.hpp"
#include "..\glcore\gl_core_4_5.h"
#include "glfw3.h"

#include <fstream>
#include <sstream>

using uint = unsigned int;

int main()
{

	// *** Initalise *** ///
	if (glfwInit() == false)
		return -1;

	// - Creating a window with GLFW:
	GLFWwindow* window = glfwCreateWindow(1280, 720, "EBON", nullptr, nullptr);

	// Checking if the window exists; if not, then terminate the program via GLFW:
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	// - Bringing that window to the front of all applications. (Bringing it into context):
	glfwMakeContextCurrent(window);

	// - Loading the OGL functions:
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		// If the load fails, destory the window:
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	// - Checking and printing what version of OpenGL we are running:
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	// *** Mesh Data *** ///
	glm::vec3 vertices[]
	{
		glm::vec3(-0.5f,  0.5f, 0.0f),
		glm::vec3( 0.5f,  0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3( 0.5f,  0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3( 0.5f, -0.5f, 0.0f),
	};


	// *** Create and load mesh *** /// 
	uint VAO;
	uint VBO;
	//uint IBO;

	// generating vao & vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// binding vao and vbo
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &verticies[0], GL_STATIC_DRAW);

	// creating vertix attribute pointer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	// unbinding
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// *** Camera *** ///
	glm::mat4 projection = glm::perspective(90.0f, 16 / 9.0f, 0.1f, 5.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::mat4(1);


	// *** Load shader from file into string *** //
	uint vertex_shader_ID = 0;
	uint fragment_shader_ID = 0;
	uint shader_progam_ID = 0;

	std::string shader_data;
	std::ifstream in_file_stream("..\\Shaders\\simple_vertex.glsl", std::ifstream::in);

	// Load source into string for compile
	std::stringstream string_stream;
	if (in_file_stream.is_open())
	{
		string_stream << in_file_stream.rdbuf();
		shader_data = string_stream.str();
		in_file_stream.close();
	}

	// Allocate space for shader program
	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	// Convert to raw char*
	const char* data = shader_data.c_str();
	// Send in the char* to shader location
	glShaderSource(vertex_shader_ID, 1, (const GLchar**)&data, 0);
	// Build!
	glCompileShader(vertex_shader_ID);

	// Did it work?
	// Check the shader compiled
	GLint success = GL_FALSE;
	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		printf("Vertex shader failed!\n");
	}


	// *** Fragment shader loading *** //
	std::ifstream in_file_stream_frag("..\\Shaders\\simple_fragment.glsl", std::ifstream::in);
	std::stringstream frag_string_stream;

	// Load source into string for compile
	if (in_file_stream_frag.is_open())
	{
		frag_string_stream << in_file_stream_frag.rdbuf();
		shader_data = frag_string_stream.str();
		in_file_stream_frag.close();
	}

	// Allocate space for shader program
	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	// Convert to raw char*
	data = shader_data.c_str();
	// Send in the char* to shader location
	glShaderSource(fragment_shader_ID, 1, (const GLchar**)&data, 0);
	// Build!
	glCompileShader(fragment_shader_ID);

	// Did it work?
	// Check the shader compiled
	success = GL_FALSE;
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		printf("Fragment shader failed!\n");
	}

	// Linking the shaders!
	shader_progam_ID = glCreateProgram();

	glAttachShader(shader_progam_ID, vertex_shader_ID);
	glAttachShader(shader_progam_ID, fragment_shader_ID);

	glLinkProgram(shader_progam_ID);

	success = GL_FALSE;
	glGetProgramiv(shader_progam_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		printf("Shader linking failed!");
	}

	// Clearing color
	glClearColor(0, 0, 0, 1.0);

	// Entering a while loop until an exit event has been registered:
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Drawing test square with triangles:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 pv = projection * view;

		glm::vec4 color = glm::vec4(0.5f);

		glUseProgram(shader_progam_ID);
		auto uniform_location = glGetUniformLocation(shader_progam_ID, "projection_view_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(pv));
		uniform_location = glGetUniformLocation(shader_progam_ID, "model_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));
		uniform_location = glGetUniformLocation(shader_progam_ID, "color");
		glUniform4fv(uniform_location, 1, glm::value_ptr(color));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);



		// Updating the monitors display by swapping the back buffer with the front buffer:
		glfwSwapBuffers(window);
		
		// Polling events so that all operating system messages and events are handled correctly:
		glfwPollEvents();
	}

	// Destorying the GLFW window:
	glfwDestroyWindow(window);

	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Terminating the GLFW application:
	glfwTerminate();
	return 0;
}