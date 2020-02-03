#include "glm.hpp"
#include "..\glcore\gl_core_4_5.h"
#include "glfw3.h"

int main()
{
	// Initalise GLFW:
	if (glfwInit() == false)
		return -1;

	// Creating a window with GLFW:
	GLFWwindow* window = glfwCreateWindow(1280, 720, "EBON", nullptr, nullptr);

	// Checking if the window exists; if not, then terminate the program via GLFW:
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	// Bringing that window to the front of all applications. (Bringing it into context):
	glfwMakeContextCurrent(window);

	// Fixing up the OpenGL extentions:
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		// If the load fails, destory the window:
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	// Checking and printing what version of OpenGL we are running:
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	// Entering a while loop until an exit event has been registered:
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Render code and game logic here!

		// Updating the monitors display by swapping the back buffer:
		glfwSwapBuffers(window);
		
		// Polling events so that all operating system messages and events are handled correctly:
		glfwPollEvents();
	}

	// Destorying the GLFW window:
	glfwDestroyWindow(window);

	// Terminating the GLFW application:
	glfwTerminate();
	return 0;
}