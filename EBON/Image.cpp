#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

Image::Image(const char* textureLocation, GLenum format)
{
	// Setting the format:
	m_gl_format = format;

	// Load texture from location:
	m_gl_handle = load(textureLocation);
}

Image::~Image() {}

uint Image::load(const char* textureLocation)
{
	// Generating a new texture with OpenGL and storing it in an unsigned int:
	uint texture;
	glGenTextures(1, &texture);

	// Binding the generated texture to openGL so all the next commands affect it.
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setting the texture wrapping/filtering options:
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Texture paramenters:
	int width, height, rnChannels;

	// Load texture and store it in an unsigned char array.
	unsigned char* data = stbi_load(textureLocation, &width, &height, &rnChannels, 0);

	// Checking if the data was loaded:
	if (data)
	{
		/* ERROR HERE WHEN LOADING JPG AND PNG! RGB for JPEG, and RGBA for PNG!*/
		// Generating the texture with the data we loaded before:
		glTexImage2D(GL_TEXTURE_2D, 0, m_gl_format, width, height, 0, m_gl_format, GL_UNSIGNED_BYTE, data);
		// Generating mipmap for the image:
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "_FAILED_TO_LOAD_TEXTURE_ID_" << texture << std::endl;
	}

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