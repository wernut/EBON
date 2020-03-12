/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       RawModel.h & RawModel.cpp
 * Purpose:     Holds a mesh and the shader attached to it, to represnt a model
 *				in worldspace with no textures.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "RawModel.h"
#include "GameManager.h"

RawModel::RawModel()
{
	// Getting the shader manager instance from the GameManager singleton:
	m_shaderManager = GameManager::getInstance()->getShaderManager();

	// Setting the shader to the default shader:
	m_shader = m_shaderManager->getShader(ShaderManager::E_DEFAULT);

	// Setting the shader to "in use", for reloading purposes:
	m_shader->SetActive(true);

	// Setting the transfoms matrix to a default identity matrix:
	m_transform = glm::mat4(1.0f);

	// Setting the mesh to null:
	m_mesh = nullptr;

	// Setting the position to 0.0f:
	m_pos = glm::vec3(0.0f);
}

RawModel::RawModel(Mesh* meshType, ShaderManager::SHADER_TYPE shaderType)
{
	// Getting the shader manager instance from the GameManager singleton:
	m_shaderManager = GameManager::getInstance()->getShaderManager();

	// Setting the shader to the shaderType parameter:
	m_shader = m_shaderManager->getShader(shaderType);

	// Setting the shader to "in use", for reloading purposes:
	m_shader->SetActive(true);

	// Setting the transfoms matrix to a default identity matrix:
	m_transform = glm::mat4(1.0f);

	// Setting the mesh to the meshType parameter:
	m_mesh = meshType;

	// Setting the position to 0.0f:
	m_pos = glm::vec3(0.0f);
}

RawModel::RawModel(const char* fileLocation, ShaderManager::SHADER_TYPE shaderType)
{
	// Getting the shader manager instance from the GameManager singleton:
	m_shaderManager = GameManager::getInstance()->getShaderManager();

	// Setting the shader to the shaderType parameter:
	m_shader = m_shaderManager->getShader(shaderType);

	// Setting the shader to "in use", for reloading purposes:
	m_shader->SetActive(true);

	// Setting the transfoms matrix to a default identity matrix:
	m_transform = glm::mat4(1.0f);

	// Setting the mesh to null:
	m_mesh = NULL;

	// Setting the position to 0.0f:
	m_pos = glm::vec3(0.0f);

	// Loading the OBJMesh from the fileLocation parameter:
	if (!m_objMesh.load(fileLocation, false))
		std::cout << "_ERROR_LOADING_OBJ_FILE_AT_LOCATION_" << fileLocation << std::endl;
}

RawModel::~RawModel()
{
	// Deleting the mesh object, if it exists:
	if (m_mesh)
	{
		delete m_mesh;
		m_mesh = nullptr;
	}
}

void RawModel::Render(Camera* camera)
{
	// Binding the shader and setting the positional values inside.
	m_shader->bind();
	m_shader->setMatrix4("projection_view_matrix", camera->getProjectionView());
	m_shader->setMatrix4("model_matrix", m_transform);

	// Rendering the mesh.
	m_mesh->Render();
}

void RawModel::RenderOBJ(Camera* camera)
{
	// Binding the shader and setting the positional values inside.
	m_shader->bind();
	m_shader->setMatrix4("projection_view_matrix", camera->getProjectionView());
	m_shader->setMatrix4("model_matrix", m_transform);

	// Rendering the mesh.
	m_objMesh.draw();
}

glm::mat4 RawModel::getTransform()
{
	return m_transform;
}

void RawModel::addPosition(glm::vec3 position)
{
	// Using the glm::translate function to move the mesh to position.
	m_transform = glm::translate(m_transform, position);
	m_pos += position;
}

void RawModel::setScale(glm::vec3 scale)
{
	// Using the glm::scale function to scale the mesh.
	m_transform = glm::scale(m_transform, scale);
}

glm::vec3 RawModel::getPosition()
{
	return m_pos;
}

void RawModel::addRotation(float eularAngle, glm::vec3 axis)
{
	// Using the glm::rotate function to rotate the mesh.
	m_transform = glm::rotate(m_transform, glm::radians(eularAngle), axis);
}

ShaderProgram* RawModel::getShader()
{
	return m_shader;
}

aie::OBJMesh RawModel::getObjMesh()
{
	return m_objMesh;
}