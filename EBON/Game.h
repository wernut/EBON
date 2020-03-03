#pragma once
#include "GameManager.h"
#include "IvysaurModel.h"
#include "EarthModel.h"
#include "ModelLight.h"
#include "ShieldModel.h"


class Game
{
public:
	Game();
	~Game();

	void Run();
	void Update();
	void Render();
private:
	DirectionalLight* m_dirLight;
	ModelLight** m_modelLights;

	GameManager* m_gameManager;
	Application* m_application;
	ShaderManager* m_shaderManager;
	Camera* m_camera;
	GLFWwindow* m_window;

	EarthModel* m_earthModel;
	IvysaurModel* m_ivyModel;
	ShieldModel* m_shieldModel;

	// Key press timer:
	bool m_canReload;
	float m_reloadTimer;

	void InitModels();
};

