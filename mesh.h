#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

//vertex itself
struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec3 normal;
};

//contains info about vertices
class Mesh
{
public:
	virtual ~Mesh(); //clear memory

	void Draw(); //draw mesh

protected:
	unsigned int m_vertexData; //reference to vertex data
	unsigned int m_drawCount; //ammount of triangles

	enum
	{
		VB_POS,
		VB_COLOR,
		VB_NORMAL,
		VB_COUNT
	};
	unsigned int m_buffers[VB_COUNT]; //buffers
	unsigned int m_indeces; //indeces

	bool m_created = false; //was mesh generated at least once

	void SetVertices(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indeces, unsigned int isStatic); //finalize creation of model
};
