#pragma once
#include "Mesh.h"

using uint = unsigned int;

class Primitives
{
public:
	Primitives();
	~Primitives();

	static uint vertexCount, indexCount;
	static void generateSphere(Mesh::Vertex* &vertices, uint &vertexCount, uint* &indices, uint &indexCount, float radius, float stackCount, float sectorCount);
};

