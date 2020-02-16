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

	Mesh(uint vertexCount,    const Vertex* vertices, 
		 uint indexCount = 0, const uint* indexBuffer = NULL, 
		 bool shouldCleanUp = false);

	Mesh(uint vertexCount, const Vertex* vertices, const char* textureLocation, 
		 uint indexCount = 0, const uint* indexBuffer = NULL, 
		 bool shouldCleanUp = false);

	virtual ~Mesh();

	void initialiseCube();
	void initialise(uint vertexCount, const Vertex* vertices, uint indexCount = 0, const uint* indexBuffer = NULL);
	void render();
	// Temp texture init
	void initialiseWithTexture(uint vertexCount, const Vertex* vertices, 
							   const char* textureLocation, uint indexCount = 0,
							   const uint* indexBuffer = NULL);
};

