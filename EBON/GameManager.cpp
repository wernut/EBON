/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       GameManager.h & GameManager.cpp
 * Purpose:     To create and hold all managers.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "GameManager.h"
#include <iostream>

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager(const char* gameTitle, const int screenWidth, const int screenHeight)
{
	// Creating the application:
	m_application = nullptr;
	CreateApplication(gameTitle, screenWidth, screenHeight);

	// Creating the shader manager:
	m_shaderManager = nullptr;
	CreateShaderManager();
}

GameManager::~GameManager() 
{
	// Cleaning up instances:
	delete m_application;
	delete m_shaderManager;
}

void GameManager::CreateApplication(const char* gameTitle, const int screenWidth, const int screenHeight)
{
	// Initialising the application instance if the application pointer is null:
	if (!m_application)
	{
		m_application = new Application(gameTitle, screenWidth, screenHeight);
	}
	else
		// Otherwise print an error message:
		std::cout << "EBON: APPLICATION_FAILED_TO_INIT: m_application != nullptr" << std::endl;

}

Application* GameManager::getApplication()
{
	// Returns the application if the pointer isn't null:
	if (m_application)
	{
		return m_application;
	}
	else
		// Otherwise print an error message:
		std::cout << "FAILED_TO_GET_APPLICATION: m_application == nullptr" << std::endl;

	return nullptr;
}

void GameManager::CreateShaderManager()
{
	// Initialising the shader manager instance if the application pointer is null:
	if (!m_shaderManager)
	{
		m_shaderManager = new ShaderManager();
	}
	else
		// Otherwise print an error message:
		std::cout << "SHADERMANAGER_FAILED_TO_INIT: m_shaderManager != nullptr" << std::endl;

}

ShaderManager* GameManager::getShaderManager()
{
	// Returns the shader manager if the pointer isn't null:
	if (m_shaderManager)
	{
		return m_shaderManager;
	}
	else
		// Otherwise print an error message:
		std::cout << "FAILED_TO_GET_SHADERMANAGER: m_shaderManager == nullptr" << std::endl;

	return nullptr;
}
