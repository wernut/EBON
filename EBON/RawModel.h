#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Camera.h"

class RawModel
{
private:
	ShaderManager* m_shaderManager;
	ShaderProgram* m_shader;
	glm::mat4 m_transform;
	Mesh* m_mesh;

public:
	RawModel();
	RawModel(Mesh* meshType, ShaderManager::E_SHADER_TYPE shaderType);
	~RawModel();

	void render(Camera* camera);

	glm::mat4 getTransform();
	void setPosition(glm::vec3 position);
	void setRotation(float eularAngle, glm::vec3 axis);
};
