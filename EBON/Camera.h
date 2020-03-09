#pragma once
#include "GameManager.h"


class Camera
{
private:
	// Camera view vars:
	const float m_FOV = 1.507f;
	const float m_RATIO = 16 / 9.0f;
	const float m_NEARPLANE = 0.1f;
	const float m_FARPLANE = 150.0f;

	// Movement vars:
	float m_movementSpeed, m_movementFastSpeed, m_sensitivity;
	float m_defaultSpeed, m_defaultMovementFastSpeed, m_defaultSensitivity;
	float m_pitch, m_yaw;
	double m_mouseX, m_mouseY;
	double m_mouseLastX, m_mouseLastY;
	float m_minPitch, m_maxPitch;
	bool m_firstTimeEnter;

	// Position / Rotation:
	glm::vec3 m_direction;
	glm::vec3 m_target;
	glm::vec3 m_position;

	// Axis:
	glm::vec3 m_worldUpAxis;
	glm::vec3 m_rightAxis;
	glm::vec3 m_upAxis;
	glm::vec3 m_frontAxis;

	// Transforms:
	glm::mat4 m_worldTransform;
	glm::mat4 m_viewTransform;
	glm::mat4 m_projectionTransform;
	glm::mat4 m_projectionViewTransform;

	// Instances:
	Application* m_application;
	GLFWwindow* m_window;

	// Private functions:

	/* Updates the keyboard input: */
	void updateKeyboardInput(float deltaTime);
	/* Updates the mouse input: */
	void updateMouseInput(float deltaTime);

public:
	Camera();
	virtual ~Camera();

	/* Updates transforms, axis and input: */
	void update(float deltaTime);
	/* Sets the cameras perspective: */
	void setPerspective(float fov, float ratio, float near_, float far_);
	/* Sets the cameras look at function: (Points the camera to a position).*/
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	/* Sets the cameras position: */
	void setPosition(glm::vec3 position);
	/* Updates the projection view transform: */
	void updateProjectionViewTransform();
	/* Updates the cameras view transform to be the inverse of the world trasform: */
	void updateMatricies();

	// Getters and setters:
	void setMovementSpeed(float value);
	void setMovementFastSpeed(float value);
	void setSensitivity(float value);
	glm::mat4 getWorldTransform();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();
	glm::vec3 getPosition();
	float getMovementSpeed();
	float getMovementFastSpeed();
	float getSensitivity();
	float getDefaultMovementSpeed();
	float getDefaultMovementFastSpeed();
	float getDefaultSensitivity();
};

