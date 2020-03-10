/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       Camera.h & Camera.cpp
 * Purpose:     To serve as a perspective renderer.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#pragma once
#include "GameManager.h"

class Camera
{
public:
	/* Main Consturctor: */
	Camera();

	/* Virutal destructor: */
	virtual ~Camera();

	// Updates transforms, axis and movement input:
	void Update(float deltaTime);

	// Updates the projection view transform:
	void UpdateProjectionViewTransform();

	// Sets the cameras perspective:
	void setPerspective(float fov, float ratio, float near_, float far_);

	// Sets the cameras look at function: (Points the camera to a position).
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);

	// Sets the cameras position:
	void setPosition(glm::vec3 position);

	// Updates the cameras view transform to be the inverse of the world trasform:
	void updateMatricies();

	// Sets the movement speed:
	void setMovementSpeed(float value);

	// Sets the fast movement speed:
	void setMovementFastSpeed(float value);

	// Sets the mouse sensitivity:
	void setSensitivity(float value);

	// Returns the world transform:
	glm::mat4 getWorldTransform();

	// Returns the view transform:
	glm::mat4 getView();

	// Returns the projection matrix:
	glm::mat4 getProjection();

	// Returns the projection * view matrix:
	glm::mat4 getProjectionView();

	// Returns the camera's position in world space:
	glm::vec3 getPosition();

	// Returns the movement speed:
	float getMovementSpeed();

	// Returns the movement fast speed:
	float getMovementFastSpeed();

	// Returns the sensitivity:
	float getSensitivity();

	// Returns the default movement speed:
	float getDefaultMovementSpeed();

	// Returns the default movement fast speed:
	float getDefaultMovementFastSpeed();

	// Returns the default sensitivity:
	float getDefaultSensitivity();

private:
	// Default perspective variables:
	const float m_FOV = 1.507f;
	const float m_RATIO = 16 / 9.0f;
	const float m_NEARPLANE = 0.1f;
	const float m_FARPLANE = 150.0f;

	/* Fly camera variables */
	// ~ Movement:
	float m_movementSpeed, m_movementFastSpeed, m_sensitivity;
	float m_defaultSpeed, m_defaultMovementFastSpeed, m_defaultSensitivity;
	// ~ Mouse input:
	float m_pitch, m_yaw;
	float m_minPitch, m_maxPitch;
	double m_mouseX, m_mouseY;
	double m_mouseLastX, m_mouseLastY;
	bool m_firstTimeEnter; // First time the mouse is entering the window?

	// Axis:
	glm::vec3 m_worldUpAxis;
	glm::vec3 m_cameraRightAxis;
	glm::vec3 m_cameraUpAxis;
	glm::vec3 m_cameraFrontAxis;

	// Position / Rotation:
	glm::vec3 m_direction;
	glm::vec3 m_target;
	glm::vec3 m_position;

	// Transforms:
	glm::mat4 m_worldTransform;
	glm::mat4 m_viewTransform;
	glm::mat4 m_projectionTransform;
	glm::mat4 m_projectionViewTransform;

	// Instances:
	Application* m_application;
	GLFWwindow* m_window;

	// Updates the keyboard input using glfwGetKey:
	void updateKeyboardInput(float deltaTime);

	// Updates the mouse input:
	void updateMouseInput(float deltaTime);
};

