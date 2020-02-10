#pragma once
#include "Application.h"

class Game
{
private:
	Application* m_app;
public:
	Game();
	~Game();

	void Run();
	void Update(float deltaTime);
	//void Render(Renderer* renderer);

};

