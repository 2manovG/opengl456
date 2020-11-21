#include "cylinder.h"

//create initial cylinder
Cylinder::Cylinder()
{
	SetNumber(0.75f, 10);
}

//help function
glm::vec2 getPos2(float k, float anglePi)
{
	float angle = anglePi * 2 * 3.14159265f;
	return glm::vec2(sinf(angle), k * cosf(angle));
}
glm::vec3 getPos(float k, float anglePi, float y)
{
	glm::vec2 v2 = getPos2(k, anglePi);
	return glm::vec3(v2.x, y, v2.y);
}

//rebuild cylinder
void Cylinder::SetNumber(float k, int n)
{
	//constants
	glm::vec3 colorTop = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 colorBottom = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 colorWall = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 down = glm::vec3(0.0f, -1.0f, 0.0f);

	//create vertices
	std::vector<Vertex> vertices; //topUp, bottomDown, wallTop, wallBottom
	std::vector<unsigned int> indeces;

	//topUp
	for (int i = 0; i < n; i++)
	{
		vertices.push_back({ getPos(k, (float)i / n, 1.0f), colorTop, up });
		if (i > 0 && i < n - 1)
		{
			indeces.push_back(0);
			indeces.push_back(i);
			indeces.push_back(i + 1);
		}
	}

	//bottomDown
	for (int i = 0; i < n; i++)
	{
		vertices.push_back({ getPos(k, (float)i / n, -1.0f), colorBottom, down });
		if (i > 0 && i < n - 1)
		{
			indeces.push_back(n);
			indeces.push_back(n + i + 1);
			indeces.push_back(n + i);
		}
	}

	//walls
	for (int i = 0; i < n; i++)
	{
		glm::vec2 v1 = getPos2(k, (float)i / n), v2 = getPos2(k, (float)(i + 1) / n);

		float dx = v2.x - v1.x, dy = v2.y - v1.y, d = sqrtf(dx * dx + dy * dy);
		glm::vec3 normal = glm::vec3(-dy / d, 0.0f, dx / d);

		vertices.push_back({ glm::vec3(v1.x, 1.0f, v1.y), colorWall, normal });
		vertices.push_back({ glm::vec3(v2.x, 1.0f, v2.y), colorWall, normal });
		vertices.push_back({ glm::vec3(v2.x, -1.0f, v2.y), colorWall, normal });
		vertices.push_back({ glm::vec3(v1.x, -1.0f, v1.y), colorWall, normal });

		indeces.push_back(2 * n + 4 * i);
		indeces.push_back(2 * n + 4 * i + 2);
		indeces.push_back(2 * n + 4 * i + 1);

		indeces.push_back(2 * n + 4 * i + 2);
		indeces.push_back(2 * n + 4 * i);
		indeces.push_back(2 * n + 4 * i + 3);
	}

	//finalize
	SetVertices(vertices, indeces, GL_STATIC_DRAW);
}
