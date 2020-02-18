#pragma once
#include "..\glcore\gl_core_4_5.h"
#include <iostream>

using uint = unsigned int;

class Image
{
private:
	uint m_gl_handle;
	int m_width, m_height, m_rnChannels;
	GLenum m_gl_format;
	uint load(const char* textureLocation);

public:
	Image(const char* textureLocation, GLenum format);
	~Image();

	int getWidth();
	int getHeight();
	uint getGlHandle();
	GLenum getFormat();
};

