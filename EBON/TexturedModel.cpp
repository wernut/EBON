#include "TexturedModel.h"
#include <iostream>

TexturedModel::TexturedModel(Mesh* mesh, ShaderManager::E_SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap, Image* normalMap, Image* ambientMap, Image* glossMap) : RawModel(mesh, shaderType)
{
	m_diffuse = diffuseMap;
	m_specular = specularMap;
	m_normal = normalMap;
	m_ambient = ambientMap;
	m_gloss = glossMap;
	m_isOBJ = false;
	setTextureUnits();
}

TexturedModel::TexturedModel(const char* objLocation, ShaderManager::E_SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap, Image* normalMap, Image* ambientMap, Image* glossMap) : RawModel(objLocation, shaderType)
{
	m_diffuse = diffuseMap;
	m_specular = specularMap;
	m_normal = normalMap;
	m_ambient = ambientMap;
	m_gloss = glossMap;
	m_isOBJ = true;
	setTextureUnits();
}

TexturedModel::~TexturedModel() 
{
	if(m_diffuse)
		delete m_diffuse;
	if(m_specular)
		delete m_specular;
	if(m_normal)
		delete m_normal;	
	if(m_ambient)
		delete m_ambient;
	if(m_gloss)
		delete m_gloss;
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
	if (m_diffuse)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_diffuse->getGlHandle());
	}

	if (m_specular)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_specular->getGlHandle());
	}

	if (m_normal)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_normal->getGlHandle());
	}

	if (m_ambient)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, m_ambient->getGlHandle());
	}

	if (m_gloss)
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, m_gloss->getGlHandle());
	}

	if (m_isOBJ)
		RawModel::renderOBJ(camera);
	else
		RawModel::render(camera);
}