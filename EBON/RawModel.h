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
#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "ShaderManager.h"
#include "Mesh.h"
#include "OBJMesh.h"
#include "Camera.h"


class RawModel
{
public:
	/* Default constructor: */
	RawModel();

	/* Mesh constuctor:
		~ Mesh* meshType - Mesh object of the model. 
		~ SHADER_TYPE shaderType - SHADER_TYPE enum that the model will use.*/
	RawModel(Mesh* meshType, ShaderManager::SHADER_TYPE shaderType);

	/* OBJModel constuctor:
		~ const char* fileLocation - Location of the OBJ file the class will load.
		~ SHADER_TYPE shaderType - SHADER_TYPE enum that the model will use.*/
	RawModel(const char* fileLocation, ShaderManager::SHADER_TYPE shaderType);

	/* Virtual destructor: */
	virtual ~RawModel();

	/* Renders the mesh and applys the default shader properties. 
		~ Camera* camera - Camera object that was created for rendering. */
	void Render(Camera* camera);

	/* Renders the OBJmesh and applys the default shader properties.
		~ Camera* camera - Camera object that was created for rendering. */
	void RenderOBJ(Camera* camera);

	/* Adds position to the models transform with glm::translate()
		~ glm::vec3 position - Amount you want to add to the current position.*/
	void addPosition(glm::vec3 position);

	/* Adds rotation to the models transform with glm::rotate()
		~ float eularAngle - The angle you want to add to the current rotation. 
		~ glm::vec3 axis - The axis you want to rotate around. */
	void addRotation(float eularAngle, glm::vec3 axis);

	/* Sets the scale of the transform with glm::scale() 
		~ glm::vec3 scale - The scale you want to set the model too. */
	void setScale(glm::vec3 scale);

	// Returns the shader attached to the model.
	ShaderProgram* getShader();

	// Returns the model's transform.
	glm::mat4 getTransform();

	// Returns the model's position.
	glm::vec3 getPosition();

	// Returns the OBJ mesh of the model.
	aie::OBJMesh getObjMesh();

protected:
	// Model's transform.
	glm::mat4 m_transform;

	// Shader manager created via the GameManager.
	ShaderManager* m_shaderManager;

	// Shader the model uses to render the mesh.
	ShaderProgram* m_shader;

	// Positon of the model.
	glm::vec3 m_pos;

	// Generated mesh.
	Mesh* m_mesh;

	// OBJ mesh loaded from a file location.
	aie::OBJMesh m_objMesh;
};

