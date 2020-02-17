#pragma once
#include "ShaderManager.h"
#include "Application.h"
#include "Camera.h"
#include "GameManager.h"
#include "RawModel.h"

class Game
{
private:
	GameManager* m_gameManager;
	Application* m_application;
	ShaderManager* m_shaderManager;
	Camera* m_camera;
	GLFWwindow* m_window;

	RawModel* m_earth;
	RawModel* m_objModel;
	//RawModel* m_terrain;

	bool m_canReload;
	float m_reloadTimer;

	void InitModels();

public:
	Game();
	~Game();

	void Run();
	void Update();
	void Render();

};

