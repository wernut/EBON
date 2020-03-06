#include "Camera.h"
#include <cmath>
#include <iostream>

Camera::Camera()
{
	// Movement vars:
	movementSpeed = 3.5f;
	movementFastSpeed = 10.0f;
	sensitivity = 0.10f;
	defaultSpeed = movementSpeed;
	defaultMovementFastSpeed = movementFastSpeed;
	defaultSensitivity = sensitivity;
	pitch = 0.0f;
	yaw = -90.0f;
	mouseX = 0;
	mouseY = 0;
	mouseLastX = SCREEN_WIDTH / 2;
	mouseLastY = SCREEN_HEIGHT / 2;
	minPitch = -89.0f;
	maxPitch =  89.0f;
	firstTimeEnter = true;

	// Position / Rotation:
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	target = glm::vec3(0.0f);
	direction = glm::vec3(0);

	// Axis:
	worldUpAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	rightAxis = glm::vec3(0);
	upAxis = glm::vec3(0, 1, 0);
	frontAxis = glm::vec3(0.0f, 0.0f, -1.0f);

	// Transforms:
	view_transform = glm::mat4(1.0f);
	projection_transform = glm::perspective(fov, ratio, nearPlane, farPlane);
	projectionView_transform = projection_transform * view_transform;
	world_transform = glm::inverse(view_transform);

	// Instances:
	m_application = GameManager::getInstance()->getApplication();

	// Getting the GLFW window:
	m_window = glfwGetCurrentContext();

	// Locking the mouse:
	m_application->setMouseLock(true);
}

Camera::~Camera() {}

void Camera::update(float deltaTime) 
{
	target = frontAxis;
	direction = glm::normalize(position - target);
	rightAxis = glm::normalize(glm::cross(worldUpAxis, direction));
    upAxis = glm::cross(direction, rightAxis);

	if (m_application->getMouseLock())
		updateMouseInput(deltaTime);

	updateKeyboardInput(deltaTime);

	setPosition(position);
}

void Camera::setPerspective(float fov, float ratio, float near_, float far_)
{
	projection_transform = glm::perspective(fov, ratio, near_, far_);
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	view_transform = glm::lookAt(from, to, up);
	world_transform = glm::inverse(view_transform);
	updateProjectionViewTransform();
}

void Camera::setPosition(glm::vec3 position)
{
	view_transform = glm::lookAt(position, position + target, worldUpAxis);
	world_transform = glm::inverse(view_transform);
	updateProjectionViewTransform();
}

void Camera::updateProjectionViewTransform()
{
	projectionView_transform = projection_transform * view_transform;
}

void Camera::updateKeyboardInput(float deltaTime)
{

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		position += movementSpeed * frontAxis * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		position -= movementSpeed * frontAxis * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(frontAxis, worldUpAxis)) * movementSpeed * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(frontAxis, worldUpAxis)) * movementSpeed * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		position += movementSpeed * worldUpAxis * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		position -= movementSpeed * worldUpAxis * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		movementSpeed = movementFastSpeed;
	else
		movementSpeed = defaultSpeed;

	if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS)
		m_application->setMouseLock(false);

	if (glfwGetKey(m_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		m_application->setMouseLock(true);
}

void Camera::updateMouseInput(float deltaTime)
{
	// Get cursor pos:
	float xPos, yPos;
	m_application->getMousePos(xPos, yPos);

	// Checking if this is the first time the window has been in focus:
	if (firstTimeEnter)
	{
		mouseLastX = xPos;
		mouseLastY = yPos;
		firstTimeEnter = false;
	}

	// Calculate the offset movement between the last and current frame:
	float xOffset = (float) (xPos - mouseLastX);
	float yOffset = (float) (mouseLastY - yPos);
	mouseLastX = xPos;
	mouseLastY = yPos;

	// Multiplying the offsets by the sensitivity var:
	(xOffset *= sensitivity) * deltaTime;
	(yOffset *= sensitivity) * deltaTime;

	// Adding offset values to the yaw and pitch:
	yaw   += xOffset;
	pitch += yOffset;

	// Clamping the pitch:
	if (pitch > maxPitch)
		pitch = maxPitch;
	else if (pitch < minPitch)
		pitch = minPitch;

	// Clamping the yaw:
	yaw = glm::mod(yaw + xOffset, 360.0f);

	// Calculating final direction & adjusting the front axis:
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontAxis = glm::normalize(direction);
}

glm::mat4 Camera::getWorldTransform()
{
	return world_transform;
}

glm::mat4 Camera::getView()
{
	return view_transform;
}

glm::mat4 Camera::getProjection()
{
	return projection_transform;
}

glm::mat4 Camera::getProjectionView()
{
	return projectionView_transform;
}

void Camera::updateMatricies()
{
	view_transform = glm::inverse(world_transform);
}

glm::vec3 Camera::getPosition()	
{
	return position;
}

void Camera::setMovementSpeed(float value)
{
	movementSpeed = value;
}

void Camera::setMovementFastSpeed(float value)
{
	movementFastSpeed = value;
}

void Camera::setSensitivity(float value)
{
	sensitivity = value;
}

float Camera::getMovementSpeed()
{
	return movementSpeed;
}

float Camera::getMovementFastSpeed()
{
	return movementFastSpeed;
}

float Camera::getSensitivity()
{
	return sensitivity;
}

float Camera::getDefaultMovementSpeed()
{
	return defaultSpeed;
}

float Camera::getDefaultMovementFastSpeed()
{
	return defaultMovementFastSpeed;
}

float Camera::getDefaultSensitivity()
{
	return defaultSensitivity;
}