#include "Primitives.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

Primitives::Primitives() {}

Primitives::~Primitives(){}

Mesh* Primitives::generateSphereMesh(float radius, float stackCount, float sectorCount)
{
	std::vector<float> vertex_buffer;
	std::vector<uint>  index_buffer;
	uint vertexCount = 0;
	uint indexCount  = 0;

	float x, y, z, xy;
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
			vertex_buffer.push_back(x);
			vertex_buffer.push_back(y);
			vertex_buffer.push_back(z);
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
	Mesh::Vertex* vertices = new Mesh::Vertex[vertexCount];
	uint ni = 1;
	for (uint i = 0; i < vertexCount; ++i)
	{
		vertices[i].position.x = vertex_buffer[ni - 1];
		vertices[i].position.y = vertex_buffer[ni];
		vertices[i].position.z = vertex_buffer[ni + 1];
		vertices[i].position.w = 1.0f;
		ni += 3;
	}

	// store indices
	indexCount = index_buffer.size();
	uint* indices = new uint[indexCount];
	for (int i = 0; i < indexCount; ++i)
	{
		indices[i] = index_buffer[i];
	}

	return new Mesh(vertexCount, vertices, indexCount, indices);
}

Mesh* Primitives::generateCubeMesh(float scale)
{
	// Cube vertices:
	float s = 0.1f * scale;
	Mesh::Vertex vertices[8];
	vertices[0].position = glm::vec4(-s,  s, 0.0f, 1.0f); // Front
	vertices[1].position = glm::vec4(-s, -s, 0.0f, 1.0f);
	vertices[2].position = glm::vec4( s,  s, 0.0f, 1.0f);
	vertices[3].position = glm::vec4( s, -s, 0.0f, 1.0f);
	// -
	vertices[4].position = glm::vec4(-s,  s, -s * 2, 1.0f); // Back
	vertices[5].position = glm::vec4(-s, -s, -s * 2, 1.0f);
	vertices[6].position = glm::vec4( s,  s, -s * 2, 1.0f);
	vertices[7].position = glm::vec4( s, -s, -s * 2, 1.0f);

	// Indexed vertex positions:
	uint index_buffer[]
	{
		0, 1, 2,
		1, 2, 3, // front
		4, 5, 6,
		5, 6, 7, // back
		4, 5, 0,
		5, 0, 1, // left
		6, 7, 2,
		7, 2, 3, // right
		5, 1, 7,
		1, 7, 3, // bottom
		4, 0, 6,
		0, 6, 2, // top
	};

	return new Mesh(8, vertices, 36, index_buffer);
}