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
	/* Default/Main constructor: */
	Game();

	/* Destructor: */
	~Game();

	// Runs the game, calling all initialise functions:
	void Run();

	// Main update function (Update everything):
	void Update();

	// Main render function (Render everything):
	void Render();

private:
	// Lights:
	DirectionalLight* m_dirLight;
	ModelLight** m_modelLights;

	// Instances:
	GameManager* m_gameManager;
	Application* m_application;
	ShaderManager* m_shaderManager;
	Camera* m_camera;
	GLFWwindow* m_window;

	// Demonstration models:
	aie::OBJMesh swordAndShield;
	Model** m_modelList;

	// ImGui vars:
	ImVec4 m_modelTintColor;
	float m_movementSpeed, m_movementFastSpeed, m_sensitivity;

	// Key press timer:
	bool m_canReload;
	float m_reloadTimer;

	// Initialises all the demonstration models:
	void InitModels();

	// Renders all the ImGui GUI.
	void RenderImGui();

	// Wraps a certain index if below min or above max.
	int Wrap(int& index, int min, int max);
};

