#pragma once
#include "glm.hpp"

class DirectionalLight
{
private:
	glm::vec3 m_direction;

protected:
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_ambient;
public:
	DirectionalLight();
	DirectionalLight(glm::vec3 dir, glm::vec3 dif, glm::vec3 spe, glm::vec3 amb);
	~DirectionalLight();

	glm::vec3 getDirection();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	glm::vec3 getAmbient();
};

