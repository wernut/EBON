#pragma once
#include "glm.hpp"
#include "..\glcore\gl_core_4_5.h"

using uint = unsigned int;

class Mesh
{
private:
	bool m_shouldCleanUp;
protected:
	uint vertex_count, index_count, tri_count;
	uint VAO, VBO, IBO; 
	uint loadTexture(const char* textureLocation);
public:
	struct Vertex
	{
		glm::vec4 position;
		glm::vec2 texCoords;
		glm::vec4 normals;
	};

	Mesh();
	Mesh(Mesh* &mesh);

	// Standard mesh:
	Mesh(uint vertexCount,    const Vertex* vertices, 
		 uint indexCount = 0, const uint* indexBuffer = NULL, 
		 bool shouldCleanUp = false);

	// Textured mesh:
	Mesh(uint vertexCount, const Vertex* vertices, const char* textureLocation, 
		 uint indexCount = 0, const uint* indexBuffer = NULL, 
		 bool shouldCleanUp = false);

	virtual ~Mesh();

	// Render mesh:
	void render();

private:

	// Temp cube init:
	void initialiseCube();

	// Standard init:
	void initialise(uint vertexCount, const Vertex* vertices, uint indexCount = 0, const uint* indexBuffer = NULL);

	// Texture init:
	void initialiseWithTexture(uint vertexCount, const Vertex* vertices, 
							   const char* textureLocation, uint indexCount = 0,
							   const uint* indexBuffer = NULL);
};

