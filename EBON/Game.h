#pragma once
#include "GameManager.h"
#include "IvysaurModel.h"
#include "EarthModel.h"
#include "ModelLight.h"


class Game
{
public:
	//struct DirLight
	//{
	//	glm::vec3 direction;
	//	glm::vec3 diffuse;
	//	glm::vec3 specular;
	//	glm::vec3 ambient;
	//};

	//struct PointLight
	//{
	//	glm::vec3 position;
	//	float constant;
	//	float linear;
	//	float quadratic;
	//	glm::vec3 diffuse;
	//	glm::vec3 specular;
	//	glm::vec3 ambient;
	//};

	//struct ModelLight
	//{
	//	RawModel* model;
	//	PointLight light;
	//};

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

	// Key press timer:
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

