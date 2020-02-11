#pragma once
#include "ShaderManager.h"
#include "Application.h"

class Game
{
private:
	Application* m_application;
	ShaderManager* m_shaderManager;
public:
	Game();
	~Game();

	void Run();
	void Update();
	//void Render(Renderer* renderer);

};

