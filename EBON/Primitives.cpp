#include "Primitives.h"
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

Primitives::Primitives() {}

Primitives::~Primitives(){}

void Primitives::generateSphere(Mesh::Vertex* &vertices, uint &vertexCount, uint* &indices, uint &indexCount, float radius, float stackCount, float sectorCount)
{
	std::vector<float> vertex_buffer;
	std::vector<uint> index_buffer;
	vertexCount = 0;
	indexCount = 0;

	float x, y, z, xy;
	float sectorStep = 2 * M_PI / sectorCount;
	float stackStep = M_PI / stackCount;
	float sectorAngle, stackAngle;

	// get vertices
	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = M_PI / 2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z  = radius * sinf(stackAngle);

		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorCount;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			vertex_buffer.push_back(x);
			vertex_buffer.push_back(y);
			vertex_buffer.push_back(z);
			++vertexCount;
		}
	}

	// store vertices
	vertexCount = vertex_buffer.size();
	vertices = new Mesh::Vertex[vertexCount];
	for (int i = 1; i < vertexCount; i *= 3)
	{
		vertices[i].position.x = vertex_buffer[i - 1];
		vertices[i].position.y = vertex_buffer[i];
		vertices[i].position.z = vertex_buffer[i + 1];
	}

	// get indexes
	int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);
		k2 = k1 + sectorCount + 1;

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				index_buffer.push_back(k1);
				index_buffer.push_back(k2);
				index_buffer.push_back(k1 + 1);
				indexCount += 3;
			}

			if (i != (stackCount - 1))
			{
				index_buffer.push_back(k1 + 1);
				index_buffer.push_back(k2);
				index_buffer.push_back(k2 + 1);
				indexCount += 3;
			}
		}
	}

	// store indices
	indexCount = index_buffer.size();
	indices = new uint[indexCount];
	for (int i = 0; i < indexCount; ++i)
	{
		indices[i] = index_buffer[i];
	}
}