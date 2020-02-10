#include "Camera.h"
#include "ext.hpp"
#include "Directives.h"
#include <cmath>

Camera::Camera()
{
	// Movement vars:
	movementSpeed = 0.05f;
	pitch = 0.0f;
	yaw = -90.0f;
	sensitivity = 0.05f;
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
	upAxis = glm::vec3(0);
	frontAxis = glm::vec3(0.0f, 0.0f, -1.0f);

	// Transforms:
	view_transform = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.0f, 1.0f, 3.0f));
	projection_transform = glm::perspective(1.707f, 16 / 9.0f, 0.1f, 15.0f);
	projectionView_transform = projection_transform * view_transform;
	world_transform = glm::inverse(view_transform);


	// Capturing the mouse (hiding & locking it in the middle of the screen):
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera::~Camera() {}

void Camera::update(float deltaTime) 
{
	processKeyboardInput();
	processMouseInput();
	direction = glm::normalize(position - target);
	rightAxis = glm::normalize(glm::cross(worldUpAxis, direction));
	upAxis = glm::cross(direction, rightAxis);
	setPosition(position);
	updateProjectionViewTransform();
}

void Camera::setPerspective(float fov, float ratio, float near, float far)
{
	projection_transform = glm::perspective(fov, ratio, near, far);
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	view_transform = glm::lookAt(from, to, up);
	//updateMatricies();
}

void Camera::setPosition(glm::vec3 position)
{
	view_transform = glm::lookAt(position, position + frontAxis, upAxis);
	//updateMatricies();
}

void Camera::updateProjectionViewTransform()
{
	projectionView_transform = projection_transform * view_transform;
}

void Camera::processKeyboardInput()
{
	GLFWwindow* window = glfwGetCurrentContext();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += movementSpeed * frontAxis;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= movementSpeed * frontAxis;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(frontAxis, upAxis)) * movementSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(frontAxis, upAxis)) * movementSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		position -= movementSpeed * worldUpAxis;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		position -= movementSpeed * -worldUpAxis;
}

void Camera::processMouseInput()
{
	GLFWwindow* window = glfwGetCurrentContext();
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

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
	xOffset *= sensitivity;
	yOffset *= sensitivity;

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
	view_transform  = glm::inverse(world_transform);
	world_transform = glm::inverse(view_transform);
}