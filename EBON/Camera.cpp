#include "Camera.h"
#include "ext.hpp"

Camera::Camera()
{
	// Movement vars:
	movementSpeed = 0.05f;

	// Position / Rotation:
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	target = glm::vec3(0.0f);
	direction = glm::vec3(0);

	// Axis:
	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
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
}

Camera::~Camera() {}

void Camera::update(float deltaTime) 
{
	direction = glm::normalize(position - target);
	rightAxis = glm::normalize(glm::cross(worldUp, direction));
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
}

void Camera::setPosition(glm::vec3 position)
{
	view_transform = glm::lookAt(position, position + frontAxis, upAxis);
}

void Camera::updateProjectionViewTransform()
{
	projectionView_transform = projection_transform * view_transform;
}

void Camera::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += movementSpeed * frontAxis;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= movementSpeed * frontAxis;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(frontAxis, upAxis)) * movementSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(frontAxis, upAxis)) * movementSpeed;
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