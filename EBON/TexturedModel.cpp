/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       TexturedModel.h & TexturedModel.cpp
 * Purpose:     Applies textures to a raw model.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "TexturedModel.h"
#include <iostream>

TexturedModel::TexturedModel() : RawModel()
{
	// Setting the maps to null:
	m_imageMaps = nullptr;

	// Setting the OBJ flag to false:
	m_isOBJ = false;
}

TexturedModel::TexturedModel(Mesh* mesh, ShaderManager::SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap, Image* normalMap, Image* ambientMap, Image* glossMap) : RawModel(mesh, shaderType)
{
	// Initialising the image map array:
	m_imageMaps = new Image * [E_COUNT];

	// Setting the correct maps to the paramenters:
	m_imageMaps[E_DIFFUSE] = diffuseMap;
	m_imageMaps[E_SPECULAR] = specularMap;
	m_imageMaps[E_NORMAL] = normalMap;
	m_imageMaps[E_AMBIENT] = ambientMap;
	m_imageMaps[E_GLOSS] = glossMap;

	// Setting the OBJ flag to false:
	m_isOBJ = false;

	// Setting the texture units:
	setTextureUnits();
}

TexturedModel::TexturedModel(const char* objLocation, ShaderManager::SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap, Image* normalMap, Image* ambientMap, Image* glossMap) : RawModel(objLocation, shaderType)
{
	// Initialising the image map array:
	m_imageMaps = new Image * [E_COUNT];

	// Setting the correct maps to the paramenters:
	m_imageMaps[E_DIFFUSE] = diffuseMap;
	m_imageMaps[E_SPECULAR] = specularMap;
	m_imageMaps[E_NORMAL] = normalMap;
	m_imageMaps[E_AMBIENT] = ambientMap;
	m_imageMaps[E_GLOSS] = glossMap;

	// Setting the OBJ flag to true:
	m_isOBJ = true;

	// Setting the texture units:
	setTextureUnits();
}

TexturedModel::TexturedModel(Mesh* mesh, ShaderManager::SHADER_TYPE shaderType) : RawModel(mesh, shaderType)
{
	// Initialising the image map array:
	m_imageMaps = new Image * [E_COUNT];

	// Setting all the image maps to null:
	m_imageMaps[E_DIFFUSE] = nullptr;
	m_imageMaps[E_SPECULAR] = nullptr;
	m_imageMaps[E_NORMAL] = nullptr;
	m_imageMaps[E_AMBIENT] = nullptr;
	m_imageMaps[E_GLOSS] = nullptr;

	// Setting the OBJ flag to false:
	m_isOBJ = false;

	// Setting the texture units:
	setTextureUnits();
}

TexturedModel::TexturedModel(const char* objLocation, ShaderManager::SHADER_TYPE shaderType) : RawModel(objLocation, shaderType)
{
	// Initialising the image map array:
	m_imageMaps = new Image * [E_COUNT];

	// Setting all the image maps to null:
	m_imageMaps[E_DIFFUSE] = nullptr;
	m_imageMaps[E_SPECULAR] = nullptr;
	m_imageMaps[E_NORMAL] = nullptr;
	m_imageMaps[E_AMBIENT] = nullptr;
	m_imageMaps[E_GLOSS] = nullptr;

	// Setting the OBJ flag to false:
	m_isOBJ = true;

	// Setting the texture units:
	setTextureUnits();
}

TexturedModel::~TexturedModel() 
{
	// Deleting all the images maps, depending on if it exists or not:
	for (int i = 0; i < E_COUNT; ++i)
	{
		if (m_imageMaps[i])
		{
			delete m_imageMaps[i];
			m_imageMaps[i] = nullptr;
		}
	}

	// Deleting the image maps array:
	delete[] m_imageMaps;
}

void TexturedModel::addMap(IMAGE_MAPS eSlot, const char* imageLocation, GLenum imageFormat)
{
	// Initalising the slot with a new image, based on parameters:
	m_imageMaps[eSlot] = new Image(imageLocation, imageFormat);
}

void TexturedModel::setTextureUnits()
{
	// Binding the shader and finding the texture locations:
	m_shader->bind();
	GLint diffuseTexUniform = glGetUniformLocation(m_shader->getID(), "diffuseTexture");
	GLint specularTexUniform = glGetUniformLocation(m_shader->getID(), "specularTexture");
	GLint normalTexUniform = glGetUniformLocation(m_shader->getID(), "normalTexture");
	GLint ambientTexUniform = glGetUniformLocation(m_shader->getID(), "ambientTexture");
	GLint glossTexUniform = glGetUniformLocation(m_shader->getID(), "glossTexture");

	// Setting the texture units based on the locations found:
	if (diffuseTexUniform >= 0)
		glUniform1i(diffuseTexUniform, 0);
	if (specularTexUniform >= 0)
		glUniform1i(specularTexUniform, 1);
	if (normalTexUniform >= 0)
		glUniform1i(normalTexUniform, 2);
	if (ambientTexUniform >= 0)
		glUniform1i(ambientTexUniform, 3);	
	if (ambientTexUniform >= 0)
		glUniform1i(ambientTexUniform, 4);
}

void TexturedModel::Render(Camera* camera)
{
	// Looping through all the image maps and binding them if they exist:
	for (int i = 0; i < E_COUNT; ++i)
	{
		if (m_imageMaps[i])
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_imageMaps[i]->getGlHandle());
		}
	}

	// Checking if the model is an OBJor normal mesh, and using the base class render function to draw it to the screen.
	if (m_isOBJ)
		RawModel::RenderOBJ(camera);
	else
		RawModel::Render(camera);
}