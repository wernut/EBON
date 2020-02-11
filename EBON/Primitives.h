#pragma once
#include "Mesh.h"
#include <vector>

using uint = unsigned int;

class Primitives
{
public:
	Primitives();
	~Primitives();

	static Mesh* generateSphere(float radius, float stackCount, float sectorCount);
	static Mesh* generateCube(float scale);
	static Mesh* generatePlane(float s, float width, float height);
};

