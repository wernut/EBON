#pragma once
#include "Mesh.h"
#include <vector>

using uint = unsigned int;

class Primitives
{
public:
	Primitives();
	~Primitives();

	static Mesh* generateSphereMesh(float radius, float stackCount, float sectorCount);
	static Mesh* generateCubeMesh(float scale);
};

