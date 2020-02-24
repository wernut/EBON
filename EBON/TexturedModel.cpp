#include "TexturedModel.h"

TexturedModel::TexturedModel(Image* image, Mesh* mesh, ShaderManager::E_SHADER_TYPE shaderType) : RawModel(mesh, shaderType)
{
	m_image = image;
	m_isOBJ = false;
}

TexturedModel::TexturedModel(Image* image, const char* objLocation, ShaderManager::E_SHADER_TYPE shaderType) : RawModel(objLocation, shaderType)
{
	m_image = image;
	m_isOBJ = true;
}

TexturedModel::~TexturedModel() {}

void TexturedModel::render(Camera* camera)
{
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_image->getGlHandle());
	if (m_isOBJ)
		RawModel::renderOBJ(camera);
	else
		RawModel::render(camera);
}