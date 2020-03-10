/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       Primitives.h & Primitives.cpp
 * Purpose:     Static class that holds functions for geometry generation:
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#pragma once
#include "Mesh.h"
#include <vector>

using uint = unsigned int;

class Primitives
{
public:
	// Generates a cube and returns the mesh:
	static Mesh* generateCube();

    // Generates a sphere and returns the mesh:
	static Mesh* generateSphere(float radius, float stackCount, float sectorCount);
	static Mesh* generatePlane(float size, bool perlinY = false, uint seed = 1234);

	// Vector to array functions:
	static uint* vectorToUintArray(std::vector<uint> index_buffer, uint &indexCount);
	static Mesh::Vertex* vectorToVertexArray(std::vector<glm::vec4> vertex_buffer,std::vector<glm::vec2> uv_buffer, uint &vertexCount);
};

