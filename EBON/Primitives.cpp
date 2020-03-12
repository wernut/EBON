/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       Primitives.h & Primitives.cpp
 * Purpose:     Static class that holds functions for geometry generation:
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "Primitives.h"
#include "PerlinNoise.hpp"


Mesh* Primitives::generateCube()
{
	// Cube vertices:
	Mesh::Vertex* vertices = new Mesh::Vertex[8];

	// Positions:
	vertices[0].position = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f); // Bottom Left
	vertices[1].position = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f); // Bottom right
	vertices[2].position = glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f); // Top left
	vertices[3].position = glm::vec4(0.5f, 0.5f, 0.0f, 1.0f); // Top Right
	// -							  		 
	vertices[4].position = glm::vec4(-0.5f, -0.5f, 1.0f, 1.0f); // Bottom Left
	vertices[5].position = glm::vec4(0.5f, -0.5f, 1.0f, 1.0f);	// Bottom right
	vertices[6].position = glm::vec4(-0.5f, 0.5f, 1.0f, 1.0f);	// Top left
	vertices[7].position = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);	// Top Right

	// Textures
	vertices[0].texCoord = glm::vec2(0.0f, 0.0f);
	vertices[1].texCoord = glm::vec2(1.0f, 0.0f);
	vertices[2].texCoord = glm::vec2(0.0f, 1.0f);
	vertices[3].texCoord = glm::vec2(1.0f, 1.0f);
	// -		
	vertices[4].texCoord = glm::vec2(0.0f, 0.0f);
	vertices[5].texCoord = glm::vec2(1.0f, 0.0f);
	vertices[6].texCoord = glm::vec2(0.0f, 1.0f);
	vertices[7].texCoord = glm::vec2(1.0f, 1.0f);

	// Indexed vertex positions:
	// OpenGL by default has a counter clock-wise winding order:
	// Below are some examples of the faces if they were rotated, and what the indices would be.
	/*
		  6---7
		 /|  /|
		2---3 |
		| 4-|-5
		|/  |/
		0---1

	*/

	//  front  left   back   right  top    bottom
	/*	2---3  6---2  7---6  3---7  6---7  4---5
		|  /|  |  /|  |  /|  |  /|  |  /|  |  /|
		|/  |  |/  |  |/  |  |/  |  |/  |  |/  |
		0---1  4---0  5---4  1---5  2---3  0---1 */
	uint* indices = new uint[36]
	{
		0, 1, 3,
		0, 2, 3, // front

		4, 0, 2,
		4, 6, 2, // left

		5, 4, 6,
		5, 7, 6, // back

		1, 5, 7,
		1, 3, 7, // right

		2, 3, 7,
		2, 6, 7, // top

		0, 1, 5,
		0, 4, 5, // bottom
	};

	return new Mesh(8, vertices, 36, indices);
}

Mesh* Primitives::generateSphere(float radius, float stackCount, float sectorCount)
{
	std::vector<glm::vec4> vertex_buffer;
	std::vector<glm::vec2> uv_buffer;
	std::vector<glm::vec4> normal_buffer;
	std::vector<uint>      index_buffer;
	uint vertexCount = 0;
	uint indexCount  = 0;

	float x, y, z, xy;
	float s, t;
	float nx, ny, nz, lengthInv = 1.0f / radius;

	float sectorStep = (float)(2 * M_PI / sectorCount);
	float stackStep  = (float)(M_PI / stackCount);
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = (float)(M_PI / 2 - i * stackStep);
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);

			// Positions:
			vertex_buffer.push_back(glm::vec4(x, y, z, 1.0f));

			//Normal:
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normal_buffer.push_back(glm::vec4(nx, ny, nz, 1.0f));

			// UV positions:
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			uv_buffer.push_back(glm::vec2(s, t));

			++vertexCount;
		}
	}

	// get indexes
	uint k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = (uint)(i * (sectorCount + 1));
		k2 = (uint)(k1 + sectorCount + 1);

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				index_buffer.push_back(k1);
				index_buffer.push_back(k2);
				index_buffer.push_back(k1 + 1);
			}

			if (i != (stackCount - 1))
			{
				index_buffer.push_back(k1 + 1);
				index_buffer.push_back(k2);
				index_buffer.push_back(k2 + 1);
			}
		}
	}

	// store vertices
	Mesh::Vertex* vertices = vectorToVertexArray(vertex_buffer, uv_buffer, vertexCount);

	// Add normals to vertices:
	for (uint i = 0; i < vertexCount; ++i)
	{
		vertices[i].normal = normal_buffer[i];
	}

	// store indices
	uint* indices = vectorToUintArray(index_buffer, indexCount);

	// creating mesh
	return new Mesh(vertexCount, vertices, indexCount, indices);
}

Mesh* Primitives::generatePlane(float size, bool perlinY, uint seed)
{
	std::vector<glm::vec4> vertex_buffer;
	std::vector<glm::vec2> uv_buffer;
	std::vector<uint>      index_buffer;
	uint vertexAndUVCount = 0;
	uint indexCount = 0;
	double elevation = 0;

	siv::PerlinNoise perlin(seed);

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			// Getting the Y level via perlin noise:
			if (perlinY)
			{
				double nx = i / size - 0.5;
				double ny = j / size - 0.5;
				elevation = 1  * perlin.noise(1 * nx, 1 * ny)
					   +  (0.5  * perlin.noise(2 * nx, 2 * ny))
					   +  (0.25 * perlin.noise(4 * nx, 4 * ny));

				elevation *= 10;
			}

			// Creating vertices & uv coords:
			vertex_buffer.push_back(glm::vec4(i, elevation, j, 1.0f));
			uv_buffer.push_back(glm::vec2((float)(i / size), (float)(j / size)));
			vertexAndUVCount++;

			if (i == 0 || j == 0) continue;

			// Creating indices:
			index_buffer.push_back(uint(size * i + j));				//Top right
			index_buffer.push_back(uint(size * i + (j - 1)));		    //Bottom right
			index_buffer.push_back(uint(size * (i - 1) + (j - 1)));	//Bottom left - First triangle

			index_buffer.push_back(uint(size * (i - 1) + (j - 1)));	//Bottom left 
			index_buffer.push_back(uint(size * (i - 1) + j));		    //Top left
			index_buffer.push_back(uint(size * i + j));				//Top right - Second triangle
		}
	}

	// store vertices
	Mesh::Vertex* vertices = vectorToVertexArray(vertex_buffer, uv_buffer, vertexAndUVCount);

	for (uint i = 0; i < vertexAndUVCount; ++i)
	{
		vertices[i].normal = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	}


	// store indices
	uint* indices = vectorToUintArray(index_buffer, indexCount);

	// Creating mesh
	return new Mesh(vertexAndUVCount, vertices, indexCount, indices);

}

uint* Primitives::vectorToUintArray(std::vector<uint> index_buffer, uint& indexCount)
{
	// Creating standard array:
	indexCount = uint(index_buffer.size());
	uint* indices = new uint[indexCount];

	// Filling the array with the vector data:
	for (size_t i = 0; i < indexCount; ++i)
	{
		indices[i] = index_buffer[i];
	}

	// Returning the array.
	return indices;
}

Mesh::Vertex* Primitives::vectorToVertexArray(std::vector<glm::vec4> vertex_buffer, std::vector<glm::vec2> uv_buffer, uint& vertexCount)
{
	// Creating standard array:
	Mesh::Vertex* vertices = new Mesh::Vertex[vertexCount];

	// Filling the array with the vector data:
	for (uint i = 0; i < vertexCount; ++i)
	{
		vertices[i].position = vertex_buffer[i];
		vertices[i].texCoord = uv_buffer[i];
	}

	// Returning the array.
	return vertices;
}
