#include "TexturedModel.h"

TexturedModel::TexturedModel(Image* image, Mesh* mesh, ShaderManager::E_SHADER_TYPE shaderType) : RawModel(mesh, shaderType)
{
	m_image = image;
}

TexturedModel::~TexturedModel() {}

void TexturedModel::render(Camera* camera)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_image->getGlHandle());
	RawModel::render(camera);
}