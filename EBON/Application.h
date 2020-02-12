#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "..\glcore\gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>

using uint = unsigned int;

class Application
{
public:
	Application(const char* gameTitle, const float screenWidth, const float screenHeight);
	~Application();

	void SetVSync(bool value);
	void Update();
	void PrintOpenGLVersion();
	void SwapBuffers();
	void ClearBuffers();
	void PollEvents();
	void ClearColor(float r, float g, float b, float a);
	void ToggleWiremeshMode();
	// Getters
	double getDeltaTime();
	double getTime();
	uint getFPS();
	bool isGameOver();
	GLFWwindow* getWindow();
	bool hasWindowClosed();
	float getWindowWidth();
	float getWindowHeight();
	void getMousePos(float &xPos, float &yPos);
	// Setters
	void setGameOver(bool value);

private:
	GLFWwindow* m_window;
	double m_deltaTime, m_lastFrame;
	double m_fpsInterval;
	uint m_fps, m_frames;
	bool m_gameOver;
	char* m_gameTitle;
	float windowWidth, windowHeight;

	int InitWindow(const char* gameTitle, const float screenWidth, const float screenHeight);
};

