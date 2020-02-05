#include "Application.h"

Application* Application::m_instance = nullptr;

Application::Application()
{
	// Creating GLFW window:
	if (InitWindow() < 0) { return; }
}

Application::~Application()
{
	// Deleting instance:
	Destroy();

	// Deleting the window:
	if (m_window)
	{
		// Shutdown GLFW:
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}

// Initialising the GLFW window: 
int Application::InitWindow()
{
	// Initalise GLFW.
	if (glfwInit() == false)
		return -1;

	// Creating the window:
	m_window = glfwCreateWindow(1280, 720, "EBON", NULL, NULL);

	// Checking if the window was successfully created:
	if (m_window == NULL)
	{
		// If fails, then terminate:
		glfwTerminate();
		return -2;
	}

	// Making the window in context on the current thread:
	glfwMakeContextCurrent(m_window);

	// Loading the OGL functions:
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		// If fails, then terminate:
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -3;
	}
}

// Printing the OpenGL version to the console:
void Application::PrintOpenGLVersion()
{
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);
}

// Wrapper for the VSync flag:
void Application::SetVSync(bool enabled)
{
	glfwSwapInterval(enabled);
}

void Application::Run()
{

}

void Application::Update()
{

}