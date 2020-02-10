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
	static void Create()
	{
		if (!m_instance)
			m_instance = new Application();
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
		APPLICATION FUNCTIONS:
	*/

	void Update();
	void PrintOpenGLVersion();
	void SetVSync(bool enabled);
	void SwapBuffers();
	void ClearBuffers();
	// Getters
	double getDeltaTime();
	double getTime();
	uint getFPS();
	bool isGameOver();
	bool hasWindowClosed();
	// Setters
	void setGameOver(bool value);

private:
	Application();
	~Application();

	/*
		APPLICATION VARIABLES:
	*/
	
	GLFWwindow* m_window;
	double m_deltaTime;
	double m_lastFrame;
	uint m_fps;
	uint m_frames;
	double m_fpsInterval;
	bool m_gameOver;

	/*
		APPLICATION FUNCTIONS:
	*/
	int InitWindow();
};

