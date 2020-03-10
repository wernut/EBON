/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       Image.h & Image.cpp
 * Purpose:     To repesent an image, and hold the necessary information needed
 *				for rendering.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/

#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

Image::Image(const char* textureLocation, GLenum format)
{
	// Setting the format:
	m_gl_format = format;

	// Load texture from location:
	m_gl_handle = Load(textureLocation);
}

Image::~Image() {}

uint Image::Load(const char* textureLocation)
{
	// Generating a new texture with OpenGL and storing it in an unsigned int:
	uint texture;
	glGenTextures(1, &texture);

	// Binding the generated texture to openGL so all the next commands affect it.
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setting the texture wrapping/filtering options:
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load texture and store it in an unsigned char array.
	unsigned char* data = stbi_load(textureLocation, &m_width, &m_height, &m_rnChannels, 0);

	// Checking if the data was loaded:
	if (data)
	{
		// Generating the texture with the data we loaded before:
		glTexImage2D(GL_TEXTURE_2D, 0, m_gl_format, m_width, m_height, 0, m_gl_format, GL_UNSIGNED_BYTE, data);
		// Generating mipmap for the image:
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "_FAILED_TO_LOAD_TEXTURE_ID_" << texture << std::endl;
	}

	// Flipping the image on load:
	stbi_set_flip_vertically_on_load(true);

	// Freeing the image memory:
	stbi_image_free(data);

	// Returning ID of texture:
	return texture;
}

int Image::getWidth()
{
	return m_width;
}

int Image::getHeight()
{
	return m_height;
}

uint Image::getGlHandle()
{
	return m_gl_handle;
}

GLenum Image::getFormat()
{
	return m_gl_format;
}