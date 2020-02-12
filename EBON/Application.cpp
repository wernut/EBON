#include "Application.h"

Application::Application(const char* gameTitle, const float windowWidth, const float windowHeight)
{
	// Creating GLFW window:
	if (InitWindow(gameTitle, windowWidth, windowHeight) < 0) { return; }

	// Init vars:
	m_deltaTime = 0.0;
	m_lastFrame = 0.0;
	m_fps = 0;
	m_frames = 0;
	m_fpsInterval = 0.0;
	m_gameOver = false;

	// Printing the version of OpenGL we are running:
	PrintOpenGLVersion();
}

Application::~Application()
{
	// Deleting the window:
	if (m_window)
	{
		// Shutdown GLFW:
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}

// Initialising the GLFW window: 
int Application::InitWindow(const char* gameTitle, const float windowWidth, const float windowHeight)
{
	// Initalise GLFW.
	if (glfwInit() == false)
		return -1;

	// Creating the window:
	m_window = glfwCreateWindow(windowWidth, windowHeight, gameTitle, NULL, NULL);

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

	return 0;
}

// Updating the application, should be called every frame:
void Application::Update()
{
	// Updating deltaTime;
	double currentFrame = getTime();
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;

	// Updating the FPS counter:
	m_frames++;
	m_fpsInterval += m_deltaTime;
	if (m_fpsInterval >= 1.0f)
	{
		m_fps = m_frames;
		m_frames = 0;
		m_fpsInterval -= 1.0f;
	}

	// Checking if the application should exit:
	m_gameOver = m_gameOver || hasWindowClosed();
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

// Getters and setters:
double Application::getDeltaTime()
{
	return m_deltaTime;
}

double Application::getTime()
{
	return glfwGetTime();
}

uint Application::getFPS()
{
	return m_fps;
}

bool Application::isGameOver()
{
	return m_gameOver;
}

bool Application::hasWindowClosed()
{
	return glfwWindowShouldClose(m_window) == GL_TRUE;
}

void Application::setGameOver(bool value)
{
	m_gameOver = value;
}

void Application::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Application::ClearBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::PollEvents()
{
	glfwPollEvents();
}

GLFWwindow* Application::getWindow()
{
	return m_window;
}

float Application::getWindowWidth()
{
	return windowWidth;
}

float Application::getWindowHeight()
{
	return windowHeight;
}

void Application::getMousePos(float& xPos, float& yPos)
{
	double _xPos, _yPos;
	glfwGetCursorPos(m_window, &_xPos, &_yPos);
	xPos = _xPos;
	yPos = _yPos;
}

void Application::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Application::ToggleWiremeshMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}