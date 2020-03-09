#include "Camera.h"
#include <cmath>
#include <iostream>

Camera::Camera()
{
	// Movement vars:
	m_movementSpeed = 3.5f;
	m_movementFastSpeed = 10.0f;
	m_sensitivity = 0.10f;
	m_defaultSpeed = m_movementSpeed;
	m_defaultMovementFastSpeed = m_movementFastSpeed;
	m_defaultSensitivity = m_sensitivity;
	m_pitch = 0.0f;
	m_yaw = -90.0f;
	m_mouseX = 0;
	m_mouseY = 0;
	m_mouseLastX = SCREEN_WIDTH / 2;
	m_mouseLastY = SCREEN_HEIGHT / 2;
	m_minPitch = -89.0f;
	m_maxPitch =  89.0f;
	m_firstTimeEnter = true;

	// Position / Rotation:
	m_position = glm::vec3(0.0f, 0.0f, 3.0f);
	m_target = glm::vec3(0.0f);
	m_direction = glm::vec3(0);

	// Axis:
	m_worldUpAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	m_rightAxis = glm::vec3(0);
	m_upAxis = glm::vec3(0, 1, 0);
	m_frontAxis = glm::vec3(0.0f, 0.0f, -1.0f);

	// Transforms:
	m_viewTransform = glm::mat4(1.0f);
	m_projectionTransform = glm::perspective(m_FOV, m_RATIO, m_NEARPLANE, m_FARPLANE);
	m_projectionViewTransform = m_projectionTransform * m_viewTransform;
	m_worldTransform = glm::inverse(m_viewTransform);

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
	m_target = m_frontAxis;
	m_direction = glm::normalize(m_position - m_target);
	m_rightAxis = glm::normalize(glm::cross(m_worldUpAxis, m_direction));
    m_upAxis = glm::cross(m_direction, m_rightAxis);

	if (m_application->getMouseLock())
		updateMouseInput(deltaTime);

	updateKeyboardInput(deltaTime);

	setPosition(m_position);
}

void Camera::setPerspective(float fov, float ratio, float near_, float far_)
{
	m_projectionTransform = glm::perspective(fov, ratio, near_, far_);
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	m_viewTransform = glm::lookAt(from, to, up);
	m_worldTransform = glm::inverse(m_viewTransform);
	updateProjectionViewTransform();
}

void Camera::setPosition(glm::vec3 position)
{
	m_viewTransform = glm::lookAt(position, position + m_target, m_worldUpAxis);
	m_worldTransform = glm::inverse(m_viewTransform);
	updateProjectionViewTransform();
}

void Camera::updateProjectionViewTransform()
{
	m_projectionViewTransform = m_projectionTransform * m_viewTransform;
}

void Camera::updateKeyboardInput(float deltaTime)
{

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_position += m_movementSpeed * m_frontAxis * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		m_position -= m_movementSpeed * m_frontAxis * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_position -= glm::normalize(glm::cross(m_frontAxis, m_worldUpAxis)) * m_movementSpeed * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		m_position += glm::normalize(glm::cross(m_frontAxis, m_worldUpAxis)) * m_movementSpeed * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_position += m_movementSpeed * m_worldUpAxis * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		m_position -= m_movementSpeed * m_worldUpAxis * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		m_movementSpeed = m_movementFastSpeed;
	else
		m_movementSpeed = m_defaultSpeed;

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
	if (m_firstTimeEnter)
	{
		m_mouseLastX = xPos;
		m_mouseLastY = yPos;
		m_firstTimeEnter = false;
	}

	// Calculate the offset movement between the last and current frame:
	float xOffset = (float) (xPos - m_mouseLastX);
	float yOffset = (float) (m_mouseLastY - yPos);
	m_mouseLastX = xPos;
	m_mouseLastY = yPos;

	// Multiplying the offsets by the sensitivity var:
	(xOffset *= m_sensitivity) * deltaTime;
	(yOffset *= m_sensitivity) * deltaTime;

	// Adding offset values to the yaw and pitch:
	m_yaw   += xOffset;
	m_pitch += yOffset;

	// Clamping the pitch:
	if (m_pitch > m_maxPitch)
		m_pitch = m_maxPitch;
	else if (m_pitch < m_minPitch)
		m_pitch = m_minPitch;

	// Clamping the yaw:
	m_yaw = glm::mod(m_yaw + xOffset, 360.0f);

	// Calculating final direction & adjusting the front axis:
	glm::vec3 direction;
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_frontAxis = glm::normalize(direction);
}

glm::mat4 Camera::getWorldTransform()
{
	return m_worldTransform;
}

glm::mat4 Camera::getView()
{
	return m_viewTransform;
}

glm::mat4 Camera::getProjection()
{
	return m_projectionTransform;
}

glm::mat4 Camera::getProjectionView()
{
	return m_projectionViewTransform;
}

void Camera::updateMatricies()
{
	m_viewTransform = glm::inverse(m_worldTransform);
}

glm::vec3 Camera::getPosition()	
{
	return m_position;
}

void Camera::setMovementSpeed(float value)
{
	m_movementSpeed = value;
}

void Camera::setMovementFastSpeed(float value)
{
	m_movementFastSpeed = value;
}

void Camera::setSensitivity(float value)
{
	m_sensitivity = value;
}

float Camera::getMovementSpeed()
{
	return m_movementSpeed;
}

float Camera::getMovementFastSpeed()
{
	return m_movementFastSpeed;
}

float Camera::getSensitivity()
{
	return m_sensitivity;
}

float Camera::getDefaultMovementSpeed()
{
	return m_defaultSpeed;
}

float Camera::getDefaultMovementFastSpeed()
{
	return m_defaultMovementFastSpeed;
}

float Camera::getDefaultSensitivity()
{
	return m_defaultSensitivity;
}