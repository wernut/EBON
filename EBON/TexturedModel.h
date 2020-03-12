/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       TexturedModel.h & TexturedModel.cpp
 * Purpose:     Applies textures to a raw model.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#pragma once
#include "RawModel.h"
#include "Image.h"

class TexturedModel : public RawModel
{
public:
	// Enum for keeping track of what map is initialised:
	enum IMAGE_MAPS
	{
		E_DIFFUSE,
		E_SPECULAR,
		E_NORMAL,
		E_AMBIENT,
		E_GLOSS,
		E_COUNT
	};

	/* Default constructor: */
	TexturedModel();

	/* Mesh* constructor: 
		~ Mesh* mesh - The mesh object the RawModel base class will use.
		~ SHADER_TYPE shaderType - The shader the model will use to apply positional and texture values to.
		~ Image* diffuseMap, specularMap, normalMap, ambientMap, glossMap - The maps that will be applied to the model. */
	TexturedModel(Mesh* mesh, ShaderManager::SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap = nullptr, Image* normalMap = nullptr, Image* ambientMap = nullptr, Image* glossMap = nullptr);

	/* OBJMesh constructor:
		~ const char* objLocation - The location of the OBJMesh that will get loaded for the model.
		~ SHADER_TYPE shaderType - The shader the model will use to apply positional and texture values to.
		~ Image* diffuseMap, specularMap, normalMap, ambientMap, glossMap - The maps that will be applied to the model. */
	TexturedModel(const char* objLocation, ShaderManager::SHADER_TYPE shaderType, Image* diffuseMap, Image* specularMap = nullptr, Image* normalMap = nullptr, Image* ambientMap = nullptr, Image* glossMap = nullptr);

	/* Mesh* constructor - All image maps will need to be set manually using the addMaps() function within a derived class:
		~ Mesh* mesh - The mesh object the RawModel base class will use.
		~ SHADER_TYPE shaderType - The shader the model will use to apply positional and texture values to. */
	TexturedModel(Mesh* mesh, ShaderManager::SHADER_TYPE shaderType);

	/* Mesh* constructor - All image maps will need to be set manually using the addMaps() function within a derived class:
		~ const char* objLocation - The location of the OBJMesh that will get loaded for the model.
		~ SHADER_TYPE shaderType - The shader the model will use to apply positional and texture values to. */
	TexturedModel(const char* objLocation, ShaderManager::SHADER_TYPE shaderType);

	/* Virtual destructor: */
	virtual ~TexturedModel();

	/* Renders the mesh and applys the default shader properties.
		~ Camera* camera - Camera object that was created for rendering. */
	void Render(Camera* camera);

protected:
	/* Adds the image maps to the image array: 
		~ IMAGE_MAPS eSlot - The slot you want to bind the image too.
		~ const char* imageLocation - The location you wish to load the image from. 
		~ GLenum imageFormat - The format of the image you are loading. */
	void addMap(IMAGE_MAPS eSlot, const char* imageLocation, GLenum imageFormat);

	// A flag to determine whether the model is obj or not.
	bool m_isOBJ;

private:
	// An array of images to store the maps within.
	Image** m_imageMaps;

	// Finds the locations of the maps within the shader and sets them to the correct texture units.
	void setTextureUnits();
};

