#include "Mesh.h"

Mesh::Mesh()
{
	vertex_count = 0;
	index_count = 0;
	tri_count = 0;
	VAO = 0;
	VBO = 0;
	IBO = 0;
}

Mesh::Mesh(Mesh* &mesh)
{
	vertex_count = mesh->vertex_count;
	index_count = mesh->index_count;
	tri_count = mesh->tri_count;
	VAO = mesh->VAO;
	VBO = mesh->VBO;
	IBO = mesh->IBO;
}

Mesh::Mesh(uint vertexCount, const Vertex* vertices, uint indexCount, const uint* indexBuffer, uint* indices)
{
	vertex_count = vertexCount;
	index_count = indexCount;
	tri_count = indexCount / 3;
	VAO = 0;
	VBO = 0;
	IBO = 0;
	initialise(vertex_count, vertices, index_count, indexBuffer, indices);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
}

void Mesh::initialiseCube()
{
	// Exiting init incase mesh has already been created:
	if (VAO != 0) return;

	// Cube vertices:
	Vertex cube_vertices[8];
	cube_vertices[0].position = glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f); // Front
	cube_vertices[1].position = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	cube_vertices[2].position = glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
	cube_vertices[3].position = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f); 
	// -
	cube_vertices[4].position = glm::vec4(-0.5f,  0.5f, -1.0f, 1.0f); // Back
	cube_vertices[5].position = glm::vec4(-0.5f, -0.5f, -1.0f, 1.0f);
	cube_vertices[6].position = glm::vec4( 0.5f,  0.5f, -1.0f, 1.0f);
	cube_vertices[7].position = glm::vec4( 0.5f, -0.5f, -1.0f, 1.0f);
	vertex_count = 8;

	// Indexed vertex positions:
	int index_buffer[]
	{
		0, 1, 2, 1, 2, 3, // front
		4, 5, 6, 5, 6, 7, // back
		4, 5, 0, 5, 0, 1, // left
		6, 7, 2, 7, 2, 3, // right
		5, 1, 7, 1, 7, 3, // bottom
		4, 0, 6, 0, 6, 2, // top
	};
	index_count = 36;
	tri_count = index_count / 3;

	// Generate buffers:
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Bind vertex array & buffer:
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), cube_vertices, GL_STATIC_DRAW);

	// Bind index buffer:
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(int), index_buffer, GL_STATIC_DRAW);

	// Create vertex attribute pointer:
	// 0 = index we're enabling and creating a pointer to
	// 4 = how many elements the attribute has
	// GL_FLOAT = type of data within that attribute
	// GL_FALSE = should we normalise the data?
	// sizeof(Vertex) = size of the data type within that attribute
	// 0 = bytes from the start of the vertex data to the first of that attribute type:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// Unbinding the buffers:
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::initialise(uint vertexCount, const Vertex* vertices, uint indexCount, const uint* indexBuffer, uint* indices)
{
	// Exiting init incase mesh has already been created:
	if (VAO != 0) return;

	// Generate buffers:
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO & VBO:
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Add vertex data to the VBO:
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	// Create vertex attribute pointer:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// Checking if the index buffer exists
	if(indexCount != 0)
	{
		// Generate index buffer:
		glGenBuffers(1, &IBO);
		// Bind it:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		// Add index array data to the IBO:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint), indexBuffer, GL_STATIC_DRAW);
		// Setting the triangle count:
		tri_count = indexCount / 3;
	}

	// Unbinding the buffers:
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Setting mesh variables:
	vertex_count = vertexCount;
	index_count = indexCount;

	if (vertices)
		delete[] vertices;

	if (indexBuffer)
		delete[] indexBuffer;
}

void Mesh::render()
{
	glBindVertexArray(VAO);
	if (IBO != 0)
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, index_count);
}