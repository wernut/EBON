#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "..\glcore\gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>

using uint = unsigned int;

class Application
{
public:
	/*
		SINGLETON FUNCTIONS:
	*/

	static Application* m_instance;

	// Creating the singleton instance:
	static Application* Create(const char* gameTitle, const float windowWidth, const float windowHeight)
	{
		if (!m_instance)
		{
			m_instance = new Application(gameTitle, windowWidth, windowHeight);
			return m_instance;
		}
	}

	// Cleaing up the singleton instance:
	static void Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	static Application* getInstance() { return m_instance; }

	/*
		APPLICATION FUNCTIONS / OPENGL WRAPPER:
	*/
	void SetVSync(bool value);
	void Update();
	void PrintOpenGLVersion();
	void SwapBuffers();
	void ClearBuffers();
	void PollEvents();
	void ClearColor(float r, float g, float b, float a);
	void ToggleWiremeshMode();
	// Getters
	double getDeltaTime();
	double getTime();
	uint getFPS();
	bool isGameOver();
	bool hasWindowClosed();
	float getWindowWidth();
	float getWindowHeight();
	// Setters
	void setGameOver(bool value);

protected:
	Application(const char* gameTitle, const float screenWidth, const float screenHeight);
	~Application();

	/*
		APPLICATION VARIABLES:
	*/
	
	GLFWwindow* m_window;
	double m_deltaTime, m_lastFrame;
	double m_fpsInterval;
	uint m_fps, m_frames;
	bool m_gameOver;
	char* m_gameTitle;
	float windowWidth, windowHeight;

	/*
		APPLICATION FUNCTIONS:
	*/
	int InitWindow(const char* gameTitle, const float screenWidth, const float screenHeight);
};

