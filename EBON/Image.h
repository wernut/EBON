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
#pragma once
#include "..\glcore\gl_core_4_5.h"
#include <iostream>

using uint = unsigned int;

class Image
{
public:
	/* Main Constuctor:
		~ textureLocation - Location of the image.
		~ format - The format of the image.
	*/
	Image(const char* textureLocation, GLenum format);\

	/* Destructor: */
	~Image();

	// Returns the width of the image:
	int getWidth();
	
	// Returns the height of the image:
	int getHeight();

	// Returns the handle of the image. (Where it's stored on the GPU).
	uint getGlHandle();

	// Returns the format of the image:
	GLenum getFormat();
private:
	
	// Where the image is stored on the gpu:
	uint m_gl_handle;

	// Width, height and rnChannels of the image:
	int m_width, m_height, m_rnChannels;

	// Format:
	GLenum m_gl_format;

	// Returns an int assigned to by OpenGL that represents the location of where the image is stored on the GPU.
	uint Load(const char* textureLocation);
};

