#include "TexturedModel.h"

TexturedModel::TexturedModel(Mesh* mesh, ShaderManager::E_SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap, Image* normalMap) : RawModel(mesh, shaderType)
{
	m_diffuse = diffuseMap;
	m_specular = specularMap;
	m_normal = normalMap;
	m_isOBJ = false;
	SetMaps();
}

TexturedModel::TexturedModel(const char* objLocation, ShaderManager::E_SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap, Image* normalMap) : RawModel(objLocation, shaderType)
{
	m_diffuse = diffuseMap;
	m_specular = specularMap;
	m_normal = normalMap;
	m_isOBJ = true;
	SetMaps();
}

TexturedModel::~TexturedModel() 
{
	delete m_diffuse;
	delete m_specular;
	delete m_normal;
}

void TexturedModel::SetMaps()
{
	if (m_diffuse)
		this->getShader()->setInt("diffuseTexture", m_diffuse->getGlHandle());

	if (m_specular)
		this->getShader()->setInt("specularTexture", m_specular->getGlHandle());

	if (m_normal)
		this->getShader()->setInt("normalTexture", m_normal->getGlHandle());
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

	if (m_isOBJ)
		RawModel::renderOBJ(camera);
	else
		RawModel::render(camera);
}