#pragma once
#include "RawModel.h"
#include "Image.h"

class TexturedModel : public RawModel
{
private:
	Image* m_diffuse;
	Image* m_specular;
	Image* m_normal;

	bool m_isOBJ;

	void SetMaps();
public:
	TexturedModel(Mesh* mesh, ShaderManager::E_SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap = nullptr, Image* normalMap = nullptr);
	TexturedModel(const char* objLocation, ShaderManager::E_SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap = nullptr, Image* normalMap = nullptr);
	~TexturedModel();

	void render(Camera* camera);
};

