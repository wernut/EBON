#pragma once
#include "glm.hpp"
#include "..\glcore\gl_core_4_5.h"

using uint = unsigned int;

class Mesh
{
public:
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

protected:
	uint m_vertexCount, m_indexCount, m_triCount;
	uint m_VAO, m_VBO, m_IBO;
	const Vertex* m_vertices;
	const uint* m_indices;
public:
	Mesh();
	Mesh(Mesh* &mesh);

	// Standard mesh:
	Mesh(uint vertexCount, const Vertex* vertices,
		 uint indexCount = 0, const uint* indexBuffer = nullptr);

	virtual ~Mesh();

	// Render mesh:
	void render();

	// Standard init:
	void initialise();
};

