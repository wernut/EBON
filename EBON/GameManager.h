/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       GameManager.h & GameManager.cpp
 * Purpose:     To create and hold all managers.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#pragma once
#include "ShaderManager.h"
#include "Application.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class GameManager
{
private:
	/* Main Constructor:
			// All variables get passed to the CreateApplication function.
			~ gameTitle - Window title.
			~ windowWidth - Window width.
			~ windowHeight - Window height.
	*/
	GameManager(const char* gameTitle, const float windowWidth, const float windowHeight);
	/*
		Destructor:
	*/
	~GameManager();

	// Singleton instance variable:
	static GameManager* m_instance;

	// Application instance:
	Application* m_application;

	// Shader Manager instance:
	ShaderManager* m_shaderManager;

	// Create the application:
	void CreateApplication(const char* gameTitle, const float windowWidth, const float windowHeight);

	// Create the shader manager:
	void CreateShaderManager();

public:
	
	/*
		Singleton create function:	
			// All variables get passed to the main constructor:
			~ gameTitle - Window title.
			~ windowWidth - Window width.
			~ windowHeight - Window height.
	*/
	static GameManager* Create(const char* gameTitle, const float windowWidth, const float windowHeight)
	{
		if (!m_instance)
		{
			m_instance = new GameManager(gameTitle, windowWidth, windowHeight);
			return m_instance;
		}

		return nullptr;
	}

	// Destroys the singleton instace:
	static void Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	// Returns the game manager singleton instace:
	static GameManager* getInstance() { return m_instance; }

	// Returns the application instance, must be accessed through getInstance():
	Application* getApplication();

	// Returns the shader manager instance, must be accessed through getInstance():
	ShaderManager* getShaderManager();
};

