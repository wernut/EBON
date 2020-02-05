#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "..\glcore\gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>

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
		else
			std::cout << "Error creating application: Application already exists!" << std::endl;
	}

	// Cleaing up the singleton instance:
	void Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
		else
			std::cout << "Error deleting application: Application doesn't exist!" << std::endl;
	}

	/*
		APPLICATION FUNCTIONS:
	*/

	void PrintOpenGLVersion();
	void SetVSync(bool enabled);
	void Run();

private:
	Application();
	~Application();

	/*
		APPLICATION VARIABLES:
	*/
	
	GLFWwindow* m_window;

	/*
		APPLICATION FUNCTIONS:
	*/
	int InitWindow();
	void Update();
};

