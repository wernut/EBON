#pragma once
#include "Mesh.h"
#include <vector>

using uint = unsigned int;

class Primitives
{
public:
	// Procedual geometry:
	static Mesh* generateCube(const char* fileLocation = "");
	static Mesh* generateSphere(float radius, float stackCount, float sectorCount, const char* fileLocation = "");
	static Mesh* generatePlane(float size, const char* fileLocation = "", bool perlinY = false, uint seed = 1234);

	// Vector to array functions:
	static uint* vectorToUintArray(std::vector<uint> index_buffer, uint &indexCount);
	static Mesh::Vertex* vectorToVertexArray(std::vector<glm::vec4> vertex_buffer,std::vector<glm::vec2> uv_buffer, uint &vertexCount);
};

