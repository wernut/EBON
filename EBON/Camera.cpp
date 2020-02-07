#include "Camera.h"
#include "ext.hpp"

Camera::Camera()
{
	lookAtRot = glm::vec3(0, 0, 1);
	position = glm::vec3(0);
	axis = glm::vec3(0, 1, 0);
	view_transform = glm::lookAt(lookAtRot, position, axis);
	projection_transform = glm::perspective(1.707f, 16 / 9.0f, 0.1f, 5.0f);
	projectionView_transform = projection_transform * view_transform;
	world_transform = glm::inverse(view_transform);
}

Camera::~Camera() {}

void Camera::update(float deltaTime) 
{
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
	view_transform = glm::lookAt(lookAtRot, position, axis);
}

void Camera::updateProjectionViewTransform()
{
	projectionView_transform = projection_transform * view_transform;
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