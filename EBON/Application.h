/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       Application.h & Application.cpp
 * Purpose:     Initialise GLFW. Keep track of deltaTime, FPS, gameOver state
 *				and the resizing of the window. Also serves as a wrapper for
 *				some OpenGL calls.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/

#pragma once
// Math library:
#include "glm.hpp"
#include "ext.hpp"
// OpenGL loader:
#include "..\glcore\gl_core_4_5.h"
// Window:
#include "glfw3.h"
// ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
// Console:
#include <iostream>

// Unsigned int = unit:
using uint = unsigned int;

class Application
{
public:
	/*
		Main Constructor:
			~ gameTitle - Title of the window.
			~ screenWidth - Initial width of the screen.
			~ screenHeight - Initial height of the screen.
	*/
	Application(const char* gameTitle, const float screenWidth, const float screenHeight);

	/*
		Destructor:
	*/
	~Application();

	/*
		Update function:
			~ Updates the deltaTime value.
			~ Keeps track of frames per second.
			~ Checks if the applications should close via the gameOver & hasWindowClosed() flags.
			~ Updates the window size: #TODO: Make this a function, currently just resizes every frame.
		~
	*/
	void Update();


	// Sets the VSync value to paramenter:
	void SetVSync(bool value);

	// Prints the OpenGL version to the console:
	void PrintOpenGLVersion();

	// Swaps the front buffer with the back buffer:
	void SwapBuffers();

	// Clears the depth and color buffer:
	void ClearBuffers();

	// Checks for input:
	void PollEvents();

	// Clears the color of the window
	void ClearColor(float r, float g, float b, float a);

	// Toggles the wiremesh mode via glPolygonMode:
	void ToggleWiremeshMode();

	// Returns deltaTime between frames:
	double getDeltaTime();

	// Returns time since application started:
	double getTime();

	// Returns frames per second:
	uint getFPS();

	// Returns the gameOver flag:
	bool isGameOver();

	// Returns GLFW's current context:
	GLFWwindow* getWindow();

	// Returns true if the GLFW window has closed:
	bool hasWindowClosed();

	// Returns the current window width:
	float getWindowWidth();

	// Returns the current window height:
	float getWindowHeight();

	// Returns the mouse position within the window:
	void getMousePos(double &xPos, double &yPos);

	// Returns true if the mouse is locked:
	bool getMouseLock();

	// Sets the gameOver flag:
	void setGameOver(bool value);

	// Sets the mouse lock flag:
	void setMouseLock(bool value);

	// Toggles the mouse locked flag:
	void toggleMouseLock();

private:
	// Window pointer to current context:
	GLFWwindow* m_window;
	
	// Delta time variables:
	double m_deltaTime, m_lastFrame;
	double m_fpsInterval;

	// FPS counter variables:
	uint m_fps, m_frames;

	// GameOver flag:
	bool m_gameOver;

	// Window title:
	char* m_gameTitle;

	// Wire mesh mode:
	bool m_wireMeshMode;

	// Mouse locked flag:
	bool m_bIsMouseLocked;

	// Current window resolution:
	float m_windowWidth, m_windowHeight;

	// Initialises GLFW's window:
	int InitWindow(const char* gameTitle, const float screenWidth, const float screenHeight);

	// Initialises ImGui:
	void InitImGui();
};

