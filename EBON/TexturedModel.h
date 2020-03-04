#pragma once
#include "RawModel.h"
#include "Image.h"

class TexturedModel : public RawModel
{
public:
	enum IMAGE_MAPS
	{
		E_DIFFUSE,
		E_SPECULAR,
		E_NORMAL,
		E_AMBIENT,
		E_GLOSS,
		E_COUNT
	};

	TexturedModel(Mesh* mesh, ShaderManager::SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap = nullptr, Image* normalMap = nullptr, Image* ambientMap = nullptr, Image* glossMap = nullptr);
	TexturedModel(const char* objLocation, ShaderManager::SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap = nullptr, Image* normalMap = nullptr, Image* ambientMap = nullptr, Image* glossMap = nullptr);

	TexturedModel(Mesh* mesh, ShaderManager::SHADER_TYPE shaderType);
	TexturedModel(const char* objLocation, ShaderManager::SHADER_TYPE shaderType);
	~TexturedModel();

	void render(Camera* camera);

	void setIsOBJMesh(bool value);
	bool getIsOBJMesh();

protected:
	void addMap(IMAGE_MAPS eSlot, const char* imageLocation, GLenum imageFormat);
	bool m_isOBJ;

private:
	Image** m_imageMaps;

	void setTextureUnits();
};

