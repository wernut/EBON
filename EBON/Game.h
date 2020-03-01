#pragma once
#include "GameManager.h"

#include "TexturedModel.h"

class Game
{
public:
	struct DirLight
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
private:
	DirLight m_light;
	glm::vec3 m_ambientLight;


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

