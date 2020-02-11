#include "RawModel.h"

RawModel::RawModel()
{
	m_shaderManager = ShaderManager::getInstance();
	m_shader = m_shaderManager->getShader(ShaderManager::DEFAULT);
	m_transform = glm::mat4(1.0f);
	m_mesh = NULL;
	m_useOBJ = false;
}

// MeshType must constuct new mesh!
RawModel::RawModel(Mesh* meshType, ShaderManager::E_SHADER_TYPE shaderType)
{
	m_shaderManager = ShaderManager::getInstance();
	m_shader = m_shaderManager->getShader(shaderType);
	m_transform = glm::mat4(1.0f);
	m_mesh = meshType;
	m_useOBJ = false;
}

// MeshType must constuct new mesh!
RawModel::RawModel(const char* fileLocation, ShaderManager::E_SHADER_TYPE shaderType)
{
	m_shaderManager = ShaderManager::getInstance();
	m_shader = m_shaderManager->getShader(shaderType);
	m_transform = glm::mat4(1.0f);
	m_mesh = NULL;
	m_useOBJ = m_objMesh.load(fileLocation, false);
	int a = 0;
}

RawModel::~RawModel()
{
	if (m_mesh)
		delete m_mesh;
}

void RawModel::draw(Camera* camera)
{
	glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

	m_shader->use();
	m_shader->setMatrix4("projection_view_matrix", camera->getProjectionView());
	m_shader->setMatrix4("model_matrix", m_transform);
	m_shader->setVector4("color", color);

	if (!m_useOBJ)
		m_mesh->render();
	else
		m_objMesh.draw();

	m_shader->stop();
}

glm::mat4 RawModel::getTransform()
{
	return m_transform;
}

void RawModel::setPosition(glm::vec3 position)
{
	m_transform = glm::translate(m_transform, position);
}

void RawModel::setRotation(float eularAngle, glm::vec3 axis)
{
	m_transform = glm::rotate(m_transform, glm::radians(eularAngle), axis);
}