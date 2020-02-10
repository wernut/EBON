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
	void Update();
	//void Render(Renderer* renderer);

};

