#pragma once
#include "glm.hpp"

class Camera
{
private:
	glm::vec3 lookAtRot;
	glm::vec3 position;
	glm::vec3 axis;

	glm::mat4 world_transform;
	glm::mat4 view_transform;
	glm::mat4 projection_transform;
	glm::mat4 projectionView_transform;

public:
	Camera();
	virtual ~Camera();

	void update(float deltaTime);
	void setPerspective(float fov, float ratio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	void updateProjectionViewTransform();
	glm::mat4 getWorldTransform();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();
};

