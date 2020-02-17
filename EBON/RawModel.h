#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "ShaderManager.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Camera.h"


class RawModel
{
private:
	ShaderManager* m_shaderManager;
	ShaderProgram* m_shader;
	glm::mat4 m_transform;
	glm::vec3 m_pos;
	Mesh* m_mesh;
	aie::OBJMesh m_objMesh;

public:
	RawModel();
	// Generated mesh:
	RawModel(Mesh* meshType, ShaderManager::E_SHADER_TYPE shaderType);
	// OBJ mesh:
	RawModel(const char* fileLocation, ShaderManager::E_SHADER_TYPE shaderType);
	~RawModel();

	void render(Camera* camera);
	void renderOBJ(Camera* camera);

	glm::mat4 getTransform();
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void setRotation(float eularAngle, glm::vec3 axis);
	ShaderProgram* getShader();
};

