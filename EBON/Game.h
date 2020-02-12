#pragma once
#include "ShaderManager.h"
#include "Application.h"
#include "Camera.h"
#include "GameManager.h"

class Game
{
private:
	GameManager* m_gameManager;
	Application* m_application;
	ShaderManager* m_shaderManager;
	Camera* m_camera;
	GLFWwindow* m_window;

public:
	Game();
	~Game();

	void Run();
	void Update();
	//void Render(Renderer* renderer);

};

