#include "GameManager.h"
#include <iostream>

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager(const char* gameTitle, const float windowWidth, const float windowHeight)
{
	// Creating the application:
	m_application = nullptr;
	CreateApplication(gameTitle, windowWidth, windowHeight);

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

void GameManager::CreateApplication(const char* gameTitle, const float windowWidth, const float windowHeight)
{
	if (!m_application)
	{
		m_application = new Application(gameTitle, windowWidth, windowHeight);
	}
	else
		std::cout << "APPLICATION_FAILED_TO_INIT: ALREADY EXISTS." << std::endl;

}

Application* GameManager::getApplication()
{
	if (m_application)
	{
		return m_application;
	}
	else
		std::cout << "FAILED_TO_GET_APPLICATION: DOESN'T EXIST." << std::endl;

	return nullptr;
}

void GameManager::CreateShaderManager()
{
	if (!m_shaderManager)
	{
		m_shaderManager = new ShaderManager();
	}
	else
		std::cout << "SHADERMANAGER_FAILED_TO_INIT: ALREADY EXISTS." << std::endl;

}

ShaderManager* GameManager::getShaderManager()
{
	if (m_shaderManager)
	{
		return m_shaderManager;
	}
	else
		std::cout << "FAILED_TO_GET_SHADERMANAGER: DOESN'T EXIST." << std::endl;

	return nullptr;
}
