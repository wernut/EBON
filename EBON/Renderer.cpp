#include "Renderer.h"
#include "glm.hpp"
#include "ext.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

//uint* Renderer::GenerateSphere(float radius)
//{
//	glm::vec3 sphere_vertices[100];
//	for (int i = 0; i < 100; ++i)
//	{
//		for (int j = 0; j < 100; ++j)
//		{
//			for (int k = 0; k < 100; ++k)
//			{
//				float x = radius * cos(i) * sin(j);
//				float y = radius * sin(i) * sin(j);
//				float z = radius * cos(j);
//				sphere_vertices[i, j, k] = glm::vec3(x, y, z);
//			}
//		}
//	}
//}