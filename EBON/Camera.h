#pragma once
#include "glm.hpp"
#include "glfw3.h"


class Camera
{
private:
	// Camera view vars:
	const float fov = 1.507f;
	const float ratio = 16 / 9.0f;
	const float nearPlane = 0.1f;
	const float farPlane = 60.0f;

	// Movement vars:
	float movementSpeed;
	float pitch, yaw;
	float sensitivity;
	double mouseX, mouseY;
	double mouseLastX, mouseLastY;
	float minPitch, maxPitch;
	bool firstTimeEnter;

	// Position / Rotation:
	glm::vec3 direction;
	glm::vec3 target;
	glm::vec3 position;

	// Axis:
	glm::vec3 worldUpAxis;
	glm::vec3 rightAxis;
	glm::vec3 upAxis;
	glm::vec3 frontAxis;

	// Transforms:
	glm::mat4 world_transform;
	glm::mat4 view_transform;
	glm::mat4 projection_transform;
	glm::mat4 projectionView_transform;

	GLFWwindow* m_window;

public:
	Camera();
	virtual ~Camera();

	void update(float deltaTime);
	void setPerspective(float fov, float ratio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	void updateProjectionViewTransform();
	void updateKeyboardInput(float deltaTime);
	void updateMouseInput(float deltaTime);
	void updateMatricies();

	glm::mat4 getWorldTransform();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();
};

