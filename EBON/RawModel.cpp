#include "RawModel.h"
#include "GameManager.h"

RawModel::RawModel()
{
	m_shaderManager = GameManager::getInstance()->getShaderManager();
	m_shader = m_shaderManager->getShader(ShaderManager::DEFAULT);
	m_shader->SetInUse(true);
	m_transform = glm::mat4(1.0f);
	m_mesh = NULL;
	m_pos = glm::vec3(0.0f);
}

// meshType must constuct new mesh!
RawModel::RawModel(Mesh* meshType, ShaderManager::E_SHADER_TYPE shaderType)
{
	m_shaderManager = GameManager::getInstance()->getShaderManager();
	m_shader = m_shaderManager->getShader(shaderType);
	m_shader->SetInUse(true);
	m_transform = glm::mat4(1.0f);
	m_mesh = meshType;
	m_pos = glm::vec3(0.0f);
}

// obj constructor
RawModel::RawModel(const char* fileLocation, ShaderManager::E_SHADER_TYPE shaderType)
{
	m_shaderManager = GameManager::getInstance()->getShaderManager();
	m_shader = m_shaderManager->getShader(shaderType);
	m_shader->SetInUse(true);
	m_transform = glm::mat4(1.0f);
	m_mesh = NULL;
	m_pos = glm::vec3(0.0f);
	if (!m_objMesh.load(fileLocation, false))
		std::cout << "_ERROR_LOADING_OBJ_FILE_AT_LOCATION_" << fileLocation << std::endl;
}

RawModel::~RawModel()
{
	if (m_mesh)
		delete m_mesh;
}

void RawModel::render(Camera* camera)
{
	m_shader->use();
	m_shader->setMatrix4("projection_view_matrix", camera->getProjectionView());
	m_shader->setMatrix4("model_matrix", m_transform);
	m_mesh->render();
	m_shader->stop();
}

void RawModel::renderOBJ(Camera* camera)
{
	m_shader->use();
	m_shader->setMatrix4("projection_view_matrix", camera->getProjectionView());
	m_shader->setMatrix4("model_matrix", m_transform);
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
	m_pos = position;
}

void RawModel::setScale(glm::vec3 scale)
{
	m_transform = glm::scale(m_transform, scale);
}

glm::vec3 RawModel::getPosition()
{
	return m_pos;
}

void RawModel::setRotation(float eularAngle, glm::vec3 axis)
{
	m_transform = glm::rotate(m_transform, glm::radians(eularAngle), axis);
}

ShaderProgram* RawModel::getShader()
{
	return m_shader;
}