#pragma once
// Math library:
#include "glm.hpp"
#include "ext.hpp"
// OpenGL loader:
#include "..\glcore\gl_core_4_5.h"
// Window:
#include "glfw3.h"
// ImGui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
// Console:
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
	bool getMouseLock();
	// Setters
	void setGameOver(bool value);
	void setMouseLock(bool value);
	void toggleMouseLock();

private:
	GLFWwindow* m_window;
	double m_deltaTime, m_lastFrame;
	double m_fpsInterval;
	uint m_fps, m_frames;
	bool m_gameOver;
	char* m_gameTitle;
	bool m_wireMeshMode;
	bool m_bIsMouseLocked;
	float m_windowWidth, m_windowHeight;

	int InitWindow(const char* gameTitle, const float screenWidth, const float screenHeight);
	void InitImGui();
};

