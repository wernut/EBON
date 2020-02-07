#include "glm.hpp"
#include "ext.hpp"
#include "..\glcore\gl_core_4_5.h"
#include "glfw3.h"

#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

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

	// ------------------------------

	// *** Camera *** ///
	//glm::mat4 projection = glm::perspective(1.707f, 16 / 9.0f, 0.1f, 5.0f);
	//glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0), glm::vec3(0, 1, 0));
	
	// Testing camera:
	Camera camera;


	// Testing shader class:
	Shader testShader("..\\Shaders\\simple_vertex.glsl", "..\\Shaders\\simple_fragment.glsl");

	// Cube vertices:
	Mesh::Vertex cube_vertices[8];
	cube_vertices[0].position = glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f); // Front
	cube_vertices[1].position = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	cube_vertices[2].position = glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
	cube_vertices[3].position = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
	// -
	cube_vertices[4].position = glm::vec4(-0.5f, 0.5f, -1.0f, 1.0f); // Back
	cube_vertices[5].position = glm::vec4(-0.5f, -0.5f, -1.0f, 1.0f);
	cube_vertices[6].position = glm::vec4(0.5f, 0.5f, -1.0f, 1.0f);
	cube_vertices[7].position = glm::vec4(0.5f, -0.5f, -1.0f, 1.0f);
	//vertex_count = 8;

	// Indexed vertex positions:
	uint index_buffer[]
	{
		0, 1, 2, 1, 2, 3, // front
		4, 5, 6, 5, 6, 7, // back
		4, 5, 0, 5, 0, 1, // left
		6, 7, 2, 7, 2, 3, // right
		5, 1, 7, 1, 7, 3, // bottom
		4, 0, 6, 0, 6, 2, // top
	};

	// Testing mesh class:
	Mesh testMesh;
	glm::mat4 meshModel = glm::mat4(1);
	testMesh.initialise(8, cube_vertices, 36, index_buffer);

	// - Clearing color:
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	// - Enabling wiremesh mode:
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// - Enabling VSync:
	glfwSwapInterval(true);

	// - Entering a while loop until an exit event has been registered:
	while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// - Drawing test square with triangles:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// - Creating the PV matrix:
		//glm::mat4 pv = projection * view;
		camera.setPosition(glm::vec3(0, 0, -10));
		camera.update(0);


	    meshModel = glm::rotate(meshModel, 0.0016f, glm::vec3(1, 1, 1));
		double time = glfwGetTime();

		//float sinTime = sin(time);
		float sinTime = -1.0f;

		glClearColor(sinTime, sinTime, sinTime, 1.0f);

		// - Creating the final colour within the fragment shader:
		glm::vec4 color = glm::vec4(-sinTime, -sinTime, -sinTime, 1.0f);

		// Testing shader:
		testShader.use();
		testShader.setMatrix4("projection_view_matrix", camera.getProjectionView());
		testShader.setMatrix4("model_matrix", meshModel);
		testShader.setVector4("color", color);

		testMesh.draw();

		// Updating the monitors display by swapping the back buffer with the front buffer:
		glfwSwapBuffers(window);
		
		// Polling events so that all operating system messages and events are handled correctly:
		glfwPollEvents();
	}

	// Destorying the GLFW window:
	glfwDestroyWindow(window);

	//glDeleteBuffers(1, &VAO);
	//glDeleteBuffers(1, &VBO);

	// Terminating the GLFW application:
	glfwTerminate();
	return 0;
}