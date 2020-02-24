#pragma once
#include "GameManager.h"

#include "TexturedModel.h"

class Game
{
private:
	struct Light
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	Light m_light;

	glm::vec3 m_ambientLight;

	GameManager* m_gameManager;
	Application* m_application;
	ShaderManager* m_shaderManager;
	Camera* m_camera;
	GLFWwindow* m_window;

	TexturedModel* m_texturedModel;
	Image* m_modelTexture;
	RawModel* m_sun;

	RawModel* m_lightCube;

	TexturedModel* m_objModel;
	Image* m_objTexture;

	TexturedModel* m_grassPlane;
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

