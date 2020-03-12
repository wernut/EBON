/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       Application.h & Application.cpp
 * Purpose:     Initialise GLFW & ImGUI. Keep track of deltaTime, FPS,
 *				gameOver state and the resizing of the window. 
 *				Also serves as a wrapper for some OpenGL calls.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/

#include "Application.h"

Application::Application(const char* gameTitle, const int screenWidth, const int screenHeight)
{
	// Creating GLFW window:
	if (InitWindow(gameTitle, screenWidth, screenHeight) < 0) { return; }

	// Printing the version of OpenGL we are running:
	PrintOpenGLVersion();

	// Init ImGui:
	InitImGui();

	// Init vars:
	m_deltaTime = 0.0;
	m_lastFrame = 0.0;
	m_fps = 0;
	m_frames = 0;
	m_fpsInterval = 0.0;
	m_gameOver = false;
	m_wireMeshMode = false;
	m_bIsMouseLocked = false;
}

Application::~Application()
{
	// Deleting the window:
	if (m_window)
	{
		// Cleanup ImGui:
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		// Shutdown GLFW:
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}

int Application::InitWindow(const char* gameTitle, const int windowWidth, const int windowHeight)
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

void Application::InitImGui()
{
	// Setting context to current window:
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);

	// Setting color scheme:
	ImGui::StyleColorsDark();
}

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

	// Adjusting viewport to window size:
	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	m_windowWidth = display_w;
	m_windowHeight = display_h;
}

void Application::PrintOpenGLVersion()
{
	// Getting the major and minor version of OpenGL:
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	// Printing them to the console:
	printf("GL: %i.%i\n", major, minor);
}

void Application::SetVSync(bool enabled)
{
	// Using the GLFW function to set VSync:
	glfwSwapInterval(enabled);
}

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
	// Checking if the current window has closed with GLFW:
	return glfwWindowShouldClose(m_window) == GL_TRUE;
}

void Application::setGameOver(bool value)
{
	m_gameOver = value;
}

void Application::SwapBuffers()
{
	// Swapping the windows buffers:
	glfwSwapBuffers(m_window);
}

void Application::ClearBuffers()
{
	// Clearing the depth and color buffer:
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Application::PollEvents()
{
	// Polls current context events:
	glfwPollEvents();
}

GLFWwindow* Application::getWindow()
{
	return m_window;
}

int Application::getWindowWidth()
{
	return m_windowWidth;
}

int Application::getWindowHeight()
{
	return m_windowHeight;
}

void Application::getMousePos(double& xPos, double& yPos)
{
	// Creating 2 doubles to hold the x and y pos:
	double _xPos, _yPos;

	// Getting the positions:
	glfwGetCursorPos(m_window, &_xPos, &_yPos);

	// Setting the passed values to the new positions:
	xPos = _xPos;
	yPos = _yPos;
}

void Application::ClearColor(float r, float g, float b, float a)
{
	// Clearing the color with the OpenGL call:
	glClearColor(r, g, b, a);
}

void Application::ToggleWiremeshMode()
{
	// Setting the wiremesh flag to the flag parameter:
	m_wireMeshMode = !m_wireMeshMode;

	// Setting the wiremesh mode to either line or fill, based on that flag:
	if (m_wireMeshMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool Application::getMouseLock()
{
	return m_bIsMouseLocked;
}

void Application::setMouseLock(bool value)
{
	// Setting the mouse locked flag to the flag parameter:
	m_bIsMouseLocked = value;

	// Setting the input mode to either disabled or normal, based on that flag:
	if(m_bIsMouseLocked)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Application::toggleMouseLock()
{
	// Setting the mouse locked flag to it's opposite value:
	m_bIsMouseLocked = !m_bIsMouseLocked;
	// Using the mouseLock function with the new value:
	setMouseLock(m_bIsMouseLocked);
}