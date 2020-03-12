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

    /* Generates a sphere and returns the mesh: 
        ~ radius - Size of the sphere.
        ~ stackCount - # of stacks/tris between each poles on the Y axis. (Smoothness)
        ~ sectorCount - # of sectors/tris between each poles on the X axis. (Smoothness)
    */
	static Mesh* generateSphere(float radius, float stackCount, float sectorCount);

    /* Generates a plane and returns it as a mesh:
        ~ size - Size of the quad's X and Z.
        ~ perlinY - Should the algorithm use perlin noise for the Y level?
        ~ seed - Seed for the perlin noise.
    */
	static Mesh* generatePlane(float size, bool perlinY = false, uint seed = 1234);

    /* Takes a dynamic array (std::vector) of uints and returns a standard array of data.
        ~ index_buffer - The dynamic array of uints.
        ~ indexCount - The size of the returned array.
    */
	static uint* vectorToUintArray(std::vector<uint> index_buffer, uint &indexCount);

    /* Takes a dynamic array (std::vector) of vec4's and returns a standard array of vertex data.
        ~ vertex_buffer - The dynamic array of vec4's.
        ~ uv_buffer - The vec2 UV coords for the mesh.
        ~ indexCount - The size of the returned array.
    */
	static Mesh::Vertex* vectorToVertexArray(std::vector<glm::vec4> vertex_buffer,std::vector<glm::vec2> uv_buffer, uint &vertexCount);
};

