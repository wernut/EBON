/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       Mesh.h & Mesh.cpp
 * Purpose:     Holds the location of a mesh on the GPU.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/

#pragma once
#include "glm.hpp"
#include "..\glcore\gl_core_4_5.h"
#include "OBJMesh.h"

using uint = unsigned int;

class Mesh
{
public:
	// Vertex struct to hold certain information per vertex:
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
		glm::vec4 tangent;
	};

	// Standard init:
	void storeOnGPU();

protected:
	// Stores the count of all vertices, indices, and triangles:
	uint m_vertexCount, m_indexCount, m_triCount;
	// Stores the location of the vertex array object, vertex buffer oject and index buffer object for this mesh.
	uint m_VAO, m_VBO, m_IBO;
	// Stores the vertex array.
	const Vertex* m_vertices;
	// Stores the index array.
	const uint* m_indices;
public:
	/* Default constructor: */
	Mesh();

	/* Copy constructor: */
	Mesh(Mesh* &mesh);

	/* Main constuctor: Stores paramenters on the GPU.
		~ vertexCount - The amount of vertices the mesh has.
		~ vertices - The array of vertices the GPU will store.
		~ indexCount (Optional) - The index count of the IBO.
		~ indexBuffer (Optional) - The index buffer object the GPU with store.
	*/
	Mesh(uint vertexCount, const Vertex* vertices,
		 uint indexCount = 0, const uint* indexBuffer = nullptr);

	/* OBJMesh chunk constuctor: Creates a mesh object that stores the VAO, VBO and IBO of chunk.
		~ chunk - OBJMesh::MeshChunk that holds location of the mesh on the GPU.
	*/
	Mesh(aie::OBJMesh::MeshChunk chunk);

	/* Virtual destructor: */
	virtual ~Mesh();

	// Render mesh:
	void Render();
};

