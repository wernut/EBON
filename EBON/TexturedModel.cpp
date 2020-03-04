#include "TexturedModel.h"
#include <iostream>

TexturedModel::TexturedModel(Mesh* mesh, ShaderManager::SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap, Image* normalMap, Image* ambientMap, Image* glossMap) : RawModel(mesh, shaderType)
{
	m_imageMaps = new Image * [E_COUNT];
	m_imageMaps[E_DIFFUSE] = diffuseMap;
	m_imageMaps[E_SPECULAR] = specularMap;
	m_imageMaps[E_NORMAL] = normalMap;
	m_imageMaps[E_AMBIENT] = ambientMap;
	m_imageMaps[E_GLOSS] = glossMap;
	m_isOBJ = false;
	setTextureUnits();
}

TexturedModel::TexturedModel(const char* objLocation, ShaderManager::SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap, Image* normalMap, Image* ambientMap, Image* glossMap) : RawModel(objLocation, shaderType)
{
	m_imageMaps = new Image * [E_COUNT];
	m_imageMaps[E_DIFFUSE] = diffuseMap;
	m_imageMaps[E_SPECULAR] = specularMap;
	m_imageMaps[E_NORMAL] = normalMap;
	m_imageMaps[E_AMBIENT] = ambientMap;
	m_imageMaps[E_GLOSS] = glossMap;
	m_isOBJ = true;
	setTextureUnits();
}

TexturedModel::TexturedModel(Mesh* mesh, ShaderManager::SHADER_TYPE shaderType) : RawModel(mesh, shaderType)
{
	m_imageMaps = new Image * [E_COUNT];
	m_imageMaps[E_DIFFUSE] = nullptr;
	m_imageMaps[E_SPECULAR] = nullptr;
	m_imageMaps[E_NORMAL] = nullptr;
	m_imageMaps[E_AMBIENT] = nullptr;
	m_imageMaps[E_GLOSS] = nullptr;
	m_isOBJ = false;
	setTextureUnits();
}

TexturedModel::TexturedModel(const char* objLocation, ShaderManager::SHADER_TYPE shaderType) : RawModel(objLocation, shaderType)
{
	m_imageMaps = new Image * [E_COUNT];
	m_imageMaps[E_DIFFUSE] = nullptr;
	m_imageMaps[E_SPECULAR] = nullptr;
	m_imageMaps[E_NORMAL] = nullptr;
	m_imageMaps[E_AMBIENT] = nullptr;
	m_imageMaps[E_GLOSS] = nullptr;
	m_isOBJ = true;
	setTextureUnits();
}

TexturedModel::~TexturedModel() 
{
	for (int i = 0; i < E_COUNT; ++i)
	{
		if (m_imageMaps[i])
		{
			delete m_imageMaps[i];
			m_imageMaps[i] = nullptr;
		}
	}
	delete[] m_imageMaps;
}

void TexturedModel::addMap(IMAGE_MAPS eSlot, const char* imageLocation, GLenum imageFormat)
{
	m_imageMaps[eSlot] = new Image(imageLocation, imageFormat);
}

void TexturedModel::setTextureUnits()
{
	m_shader->bind();
	GLint diffuseTexUniform = glGetUniformLocation(m_shader->getID(), "diffuseTexture");
	GLint specularTexUniform = glGetUniformLocation(m_shader->getID(), "specularTexture");
	GLint normalTexUniform = glGetUniformLocation(m_shader->getID(), "normalTexture");
	GLint ambientTexUniform = glGetUniformLocation(m_shader->getID(), "ambientTexture");
	GLint glossTexUniform = glGetUniformLocation(m_shader->getID(), "glossTexture");

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

void TexturedModel::render(Camera* camera)
{

	for (int i = 0; i < E_COUNT; ++i)
	{
		if (m_imageMaps[i])
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_imageMaps[i]->getGlHandle());
		}
	}

	if (m_isOBJ)
		RawModel::renderOBJ(camera);
	else
		RawModel::render(camera);
}

void TexturedModel::setIsOBJMesh(bool value)
{
	m_isOBJ = value;
}

bool TexturedModel::getIsOBJMesh()
{
	return m_isOBJ;
}