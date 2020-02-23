#pragma once
#include "GameManager.h"

#include "TexturedModel.h"

class Game
{
private:
	GameManager* m_gameManager;
	Application* m_application;
	ShaderManager* m_shaderManager;
	Camera* m_camera;
	GLFWwindow* m_window;

	RawModel* m_sun;

	TexturedModel* m_earth;
	Image* m_earthImage;

	RawModel* m_objModel;

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

