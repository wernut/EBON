#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "ShaderManager.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Camera.h"


class RawModel
{
protected:
	ShaderManager* m_shaderManager;
	ShaderProgram* m_shader;
	glm::vec3 m_pos;
	Mesh* m_mesh;
	aie::OBJMesh m_objMesh;

public:
	RawModel();
	// Generated mesh:
	RawModel(Mesh* meshType, ShaderManager::SHADER_TYPE shaderType);
	// OBJ mesh:
	RawModel(const char* fileLocation, ShaderManager::SHADER_TYPE shaderType);
	~RawModel();
	glm::mat4 m_transform;

	void render(Camera* camera);
	void renderOBJ(Camera* camera);

	ShaderProgram* getShader();
	glm::mat4 getTransform();

	void addPosition(glm::vec3 position);
	glm::vec3 getPosition();

	void addRotation(float eularAngle, glm::vec3 axis);

	void setScale(glm::vec3 scale);

	aie::OBJMesh getObjMesh();
};

