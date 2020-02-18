#include "Mesh.h"
#include "GameManager.h"

Mesh::Mesh()
{
	m_vertexCount = 0;
	m_indexCount = 0;
	m_triCount = 0;
	m_VAO = 0;
	m_VBO = 0;
	m_IBO = 0;
	m_vertices = nullptr;
	m_indices = nullptr;
}

Mesh::Mesh(Mesh* &mesh)
{
	m_vertexCount = mesh->m_vertexCount;
	m_indexCount = mesh->m_indexCount;
	m_triCount = mesh->m_triCount;
	m_VAO = mesh->m_VAO;
	m_VBO = mesh->m_VBO;
	m_IBO = mesh->m_IBO;
	m_vertices = mesh->m_vertices;
	m_indices = mesh->m_indices;
}

Mesh::Mesh(uint vertexCount, const Vertex* vertices, uint indexCount, const uint* indices)
{
	m_vertexCount = vertexCount;
	m_indexCount = indexCount;
	m_triCount = indexCount / 3;
	m_vertices = vertices;
	m_indices = indices;
	m_VAO = 0;
	m_VBO = 0;
	m_IBO = 0;
	initialise();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);

	delete[] m_vertices;
	delete[] m_indices;
}

void Mesh::initialise()
{
	// Exiting init incase mesh has already been created:
	if (m_VAO != 0) return;

	// Generate buffers:
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	// Bind VAO & VBO:
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Add vertex data to the VBO:
	glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(Vertex), m_vertices, GL_STATIC_DRAW);

	// Create vertex attribute pointer:
	// 0 = index we're enabling and creating a pointer to
	// 4 = how many elements the attribute has
	// GL_FLOAT = type of data within that attribute
	// GL_FALSE = should we normalise the data?
	// sizeof(Vertex) = size of the data type within that attribute
	// 0 = bytes from the start of the vertex data to the first of that attribute type:

	// Create vertex attribute pointer to positions:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// Create attribute point to vertex texture coordinates:
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2));
	glEnableVertexAttribArray(1);

	// Checking if the index buffer exists
	if(m_indexCount != 0)
	{
		// Generate index buffer:
		glGenBuffers(1, &m_IBO);
		// Bind it:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		// Add index array data to the IBO:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(uint), m_indices, GL_STATIC_DRAW);
	}

	// Unbinding the buffers:
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::render()
{
	// Drawing either by indices or vertices:
	glBindVertexArray(m_VAO);
	if (m_IBO != 0)
		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
}

