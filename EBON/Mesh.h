#pragma once
#include "glm.hpp"
#include "..\glcore\gl_core_4_5.h"

using uint = unsigned int;

class Mesh
{
protected:
	uint vertex_count, index_count, tri_count;
	uint VAO, VBO, IBO;
public:
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 noraml;
		glm::vec4 texCoords;
	};

	Mesh();
	Mesh(Mesh* &mesh);
	Mesh(uint vertexCount, const Vertex* vertices, uint indexCount = 0, const uint* indexBuffer = NULL, uint* indices = NULL);
	virtual ~Mesh();

	void initialiseCube();
	void initialise(uint vertexCount, const Vertex* vertices, uint indexCount = 0, const uint* indexBuffer = NULL, uint* indices = NULL);
	void draw();
};

