#pragma once
#include "GameManager.h"
#include "IvysaurModel.h"
#include "EarthModel.h"
#include "ModelLight.h"
#include "ShieldModel.h"
#include "SwordModel.h"
#include "GameObject.h"


class Game
{
public:
	Game();
	~Game();

	void run();
	void update();
	void render();
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
	aie::OBJMesh swordAndShield;
	ShieldModel* m_shieldModel;
	SwordModel* m_swordModel;

	Model** m_modelList;

	// ImGui vars:
	ImVec4 m_modelTintColor;
	float m_movementSpeed, m_movementFastSpeed, m_sensitivity;
	int m_modelListIndex;

	// Key press timer:
	bool m_canReload;
	float m_reloadTimer;

	void initModels();
	void renderImGui();
	int wrap(int& index, int min, int max);
};

