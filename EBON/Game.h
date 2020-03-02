#pragma once
#include "TexturedModel.h"
#include "GameManager.h"


class Game
{
public:
	struct DirLight
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 ambient;
	};

	struct PointLight
	{
		glm::vec3 position;
		float constant;
		float linear;
		float quadratic;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 ambient;
	};

	struct ModelLight
	{
		RawModel* model;
		PointLight light;
	};

private:
	DirLight m_dirLight;
	ModelLight m_modelLights[2];

	GameManager* m_gameManager;
	Application* m_application;
	ShaderManager* m_shaderManager;
	Camera* m_camera;
	GLFWwindow* m_window;

	TexturedModel* m_earthModel;
	TexturedModel* m_ivyModel;

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

