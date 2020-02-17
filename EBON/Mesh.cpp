#include "Mesh.h"
#include "GameManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

#include <iostream>

static int index = 0;

Mesh::Mesh()
{
	vertex_count = 0;
	index_count = 0;
	tri_count = 0;
	VAO = 0;
	VBO = 0;
	IBO = 0;
	m_shouldCleanUp = false;
}

Mesh::Mesh(Mesh* &mesh)
{
	vertex_count = mesh->vertex_count;
	index_count = mesh->index_count;
	tri_count = mesh->tri_count;
	VAO = mesh->VAO;
	VBO = mesh->VBO;
	IBO = mesh->IBO;
	m_shouldCleanUp = mesh->m_shouldCleanUp;
}

Mesh::Mesh(uint vertexCount, const Vertex* vertices, uint indexCount, const uint* indexBuffer, bool shouldCleanUp)
{
	vertex_count = vertexCount;
	index_count = indexCount;
	tri_count = indexCount / 3;
	VAO = 0;
	VBO = 0;
	IBO = 0;
	m_shouldCleanUp = shouldCleanUp;
	initialise(vertex_count, vertices, index_count, indexBuffer);
}

Mesh::Mesh(uint vertexCount, const Vertex* vertices, const char* textureLocation, uint indexCount, const uint* indexBuffer, bool shouldCleanUp)
{
	vertex_count = vertexCount;
	index_count = indexCount;
	tri_count = indexCount / 3;
	VAO = 0;
	VBO = 0;
	IBO = 0;
	m_shouldCleanUp = shouldCleanUp;
	initialiseWithTexture(vertex_count, vertices, textureLocation, index_count, indexBuffer);
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

void Mesh::initialise(uint vertexCount, const Vertex* vertices, uint indexCount, const uint* indexBuffer)
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

	// Create vertex attribute pointer to positions:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//// Create attribute point to vertex normal direction:
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) + sizeof(glm::vec2)));
	//glEnableVertexAttribArray(1);

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

	// Should we clean up the passed vertices and indices?
	if (m_shouldCleanUp)
	{
		if (vertices)
			delete[] vertices;

		if (indexBuffer)
			delete[] indexBuffer;
	}
}

void Mesh::initialiseWithTexture(uint vertexCount, const Vertex* vertices, const char* textureLocation, uint indexCount, const uint* indexBuffer)
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

	// Create attribute pointer to vertex positions:
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	// Loading the texture:
	uint texture = loadTexture(textureLocation);

	// Create attribute point to vertex texture coordinates:
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(1);

	// Create attribute point to vertex normal direction:
	//glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) + sizeof(glm::vec2)));
	//glEnableVertexAttribArray(2);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);

	// Checking if the index buffer exists
	if (indexCount != 0)
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

	// Should we clean up the passed vertices and indices?
	if (m_shouldCleanUp)
	{
		if (vertices)
			delete[] vertices;

		if (indexBuffer)
			delete[] indexBuffer;
	}
}

void Mesh::render()
{
	// Drawing either by indices or vertices:
	glBindVertexArray(VAO);
	if (IBO != 0)
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

uint Mesh::loadTexture(const char* textureLocation)
{
	// Generating a new texture with OpenGL and storing it in an unsigned int:
	uint texture;
	glGenTextures(1, &texture);

	// Binding the generated texture to openGL so all the next commands affect it.
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setting the texture wrapping/filtering options:
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Texture paramenters:
	int width, height, rnChannels;

	// Load texture and store it in an unsigned char array.
	unsigned char* data = stbi_load(textureLocation, &width, &height, &rnChannels, 0);

	// Checking if the data was loaded:
	if (data)
	{
		// Generating the texture with the data we loaded before:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// Generating mipmap for the image:
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "_FAILED_TO_LOAD_TEXTURE!" << std::endl;
	}

	// Freeing the image memory:
	stbi_image_free(data);

	// Returning ID of texture:
	return texture;
}
