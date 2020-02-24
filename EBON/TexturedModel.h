#pragma once
#include "RawModel.h"
#include "Image.h"

class TexturedModel : public RawModel
{
private:
	Image* m_image;
	bool m_isOBJ;
public:
	TexturedModel(Image* image, Mesh* mesh, ShaderManager::E_SHADER_TYPE shaderType);
	TexturedModel(Image* image, const char* objLocation, ShaderManager::E_SHADER_TYPE shaderType);
	~TexturedModel();

	void render(Camera* camera);
};

