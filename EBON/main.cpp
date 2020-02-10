#include "glm.hpp"
#include "ext.hpp"
#include "..\glcore\gl_core_4_5.h"
#include "glfw3.h"

#include "Directives.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Primitives.h"

#include <fstream>
#include <sstream>

using uint = unsigned int;

int main()
{

	// *** Initalise *** ///
	if (glfwInit() == false)
		return -1;

	// - Creating a window with GLFW:
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "EBON", nullptr, nullptr);

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
		0, 1, 2, 
		1, 2, 3, // front
		4, 5, 6, 
		5, 6, 7, // back
		4, 5, 0, 
		5, 0, 1, // left
		6, 7, 2, 
		7, 2, 3, // right
		5, 1, 7, 
		1, 7, 3, // bottom
		4, 0, 6, 
		0, 6, 2, // top
	};


	Mesh::Vertex* sphere_vertices;
	uint* sphere_indices;
	uint vertexCount, indexCount;
	Primitives::generateSphere(sphere_vertices, vertexCount, 
							   sphere_indices, indexCount, 
							   1.0f, 36.0f, 18.0f);

	// Testing mesh class with above vertices:
	Mesh testMesh;
	glm::mat4 model = glm::mat4(1);
	testMesh.initialise(vertexCount, sphere_vertices, indexCount, sphere_indices);
	//testMesh.initialise(8, cube_vertices, 36, index_buffer);

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

		// Rotate the model
		//model = glm::rotate(model, 0.016f, glm::vec3(1.0f, 1.0f, 1.0f));

		// Polling events so that all operating system messages and events are handled correctly:
		glfwPollEvents();

		// - Creating the PV matrix:
		camera.update(0); 

		// - Creating the final colour within the fragment shader:
		glm::vec4 color = glm::vec4(1.0f);

		// Testing shader:
		testShader.use();
		testShader.setMatrix4("projection_view_matrix", camera.getProjectionView());
		testShader.setMatrix4("model_matrix", model);
		testShader.setVector4("color", color);

		// Drawing the mesh
		testMesh.draw();

		// Updating the monitors display by swapping the back buffer with the front buffer:
		glfwSwapBuffers(window);
	}

	// Destorying the GLFW window:
	glfwDestroyWindow(window);

	// Terminating the GLFW application:
	glfwTerminate();
	return 0;
}