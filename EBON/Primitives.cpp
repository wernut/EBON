#include "Primitives.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

#include <iostream>

Mesh* Primitives::generateCube(const char* fileLocation)
{
	// Cube vertices:
	Mesh::Vertex vertices[8];

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
	vertices[0].texCoords = glm::vec2(0.0f, 0.0f);
	vertices[1].texCoords = glm::vec2(1.0f, 0.0f);
	vertices[2].texCoords = glm::vec2(0.0f, 1.0f);
	vertices[3].texCoords = glm::vec2(1.0f, 1.0f);
	// -		
	vertices[4].texCoords = glm::vec2(0.0f, 0.0f);
	vertices[5].texCoords = glm::vec2(1.0f, 0.0f);
	vertices[6].texCoords = glm::vec2(0.0f, 1.0f);
	vertices[7].texCoords = glm::vec2(1.0f, 1.0f);

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
	uint indices[]
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

	if (fileLocation != "")
		return new Mesh(8, vertices, fileLocation, 36, indices, true);
	else
		return new Mesh(8, vertices, 36, indices, true);
}

Mesh* Primitives::generateSphere(float radius, float stackCount, float sectorCount, const char* fileLocation)
{
	std::vector<glm::vec4> vertex_buffer;
	std::vector<uint>      index_buffer;
	std::vector<glm::vec2> uv_buffer;
	uint vertexCount = 0;
	uint indexCount  = 0;

	float x, y, z, xy;
	float s, t;
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

	// store indices
	uint* indices = vectorToUintArray(index_buffer, indexCount);

	if(fileLocation != "")
		return new Mesh(vertexCount, vertices, fileLocation, indexCount, indices, true);
	else
		return new Mesh(vertexCount, vertices, indexCount, indices, true);
}

Mesh* Primitives::generatePlane(float size, const char* fileLocation)
{
	std::vector<glm::vec4> vertex_buffer;
	std::vector<glm::vec2> uv_buffer;
	std::vector<uint>      index_buffer;
	uint vertexAndUVCount = 0;
	uint indexCount = 0;
	float randY = 0;

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			randY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			//std::cout << randY << std::endl;
			vertex_buffer.push_back(glm::vec4(i, randY, j, 1.0f));
			uv_buffer.push_back(glm::vec2((float)(i / size), (float)(j / size)));
			vertexAndUVCount++;

			if (i == 0 || j == 0) continue;

			index_buffer.push_back(size * i + j);				//Top right
			index_buffer.push_back(size * i + (j - 1));		    //Bottom right
			index_buffer.push_back(size * (i - 1) + (j - 1));	//Bottom left - First triangle

			index_buffer.push_back(size * (i - 1) + (j - 1));	//Bottom left 
			index_buffer.push_back(size * (i - 1) + j);		    //Top left
			index_buffer.push_back(size * i + j);				//Top right - Second triangle
		}
	}

	// store vertices
	Mesh::Vertex* vertices = vectorToVertexArray(vertex_buffer, uv_buffer, vertexAndUVCount);

	// store indices
	uint* indices = vectorToUintArray(index_buffer, indexCount);

	if(fileLocation != "")
		return new Mesh(vertexAndUVCount, vertices, fileLocation, indexCount, indices, true);
	else
		return new Mesh(vertexAndUVCount, vertices, indexCount, indices, true);

}

uint* Primitives::vectorToUintArray(std::vector<uint> index_buffer, uint& indexCount)
{
	indexCount = index_buffer.size();
	uint* indices = new uint[indexCount];
	for (size_t i = 0; i < indexCount; ++i)
	{
		indices[i] = index_buffer[i];
	}
	return indices;
}

Mesh::Vertex* Primitives::vectorToVertexArray(std::vector<glm::vec4> vertex_buffer, std::vector<glm::vec2> uv_buffer, uint& vertexCount)
{
	Mesh::Vertex* vertices = new Mesh::Vertex[vertexCount];
	for (uint i = 0; i < vertexCount; ++i)
	{
		vertices[i].position = vertex_buffer[i];
		vertices[i].texCoords = uv_buffer[i];
	}

	return vertices;
}
