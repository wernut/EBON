#pragma once
#include "ShaderManager.h"
#include "Application.h"

class GameManager
{
private:
	GameManager(const char* gameTitle, const float windowWidth, const float windowHeight);
	~GameManager();

	static GameManager* m_instance;

	Application* m_application;
	ShaderManager* m_shaderManager;

	void CreateApplication(const char* gameTitle, const float windowWidth, const float windowHeight);
	void CreateShaderManager();

public:
	
	static GameManager* Create(const char* gameTitle, const float windowWidth, const float windowHeight)
	{
		if (!m_instance)
		{
			m_instance = new GameManager(gameTitle, windowWidth, windowHeight);
			return m_instance;
		}

		return nullptr;
	}

	static void Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	static GameManager* getInstance() { return m_instance; }

	Application* getApplication();
	ShaderManager* getShaderManager();
};

