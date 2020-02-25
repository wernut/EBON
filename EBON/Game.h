#pragma once
#include "GameManager.h"

#include "TexturedModel.h"

class Game
{
private:
	struct DirectionalLight
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct PointLight
	{
		glm::vec3 position;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	DirectionalLight m_light;

	glm::vec3 m_ambientLight;

	GameManager* m_gameManager;
	Application* m_application;
	ShaderManager* m_shaderManager;
	Camera* m_camera;
	GLFWwindow* m_window;

	TexturedModel* m_earthModel;
	Image* m_earthDiffuse;
	Image* m_earthSpecular;
	Image* m_earthNormal;

	TexturedModel* m_ivyModel;
	Image* m_ivyDiffuse;
	Image* m_ivySpecular;
	Image* m_ivyNormal;

	TexturedModel* m_grassModel;
	Image* m_grassTexture;

	TexturedModel* m_lampModel;
	Image* m_lampTexture;

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

