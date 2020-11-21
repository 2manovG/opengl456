#include "octahedron.h"
#include <cmath>

//set vertices
Octahedron::Octahedron()
{
    glm::vec3 color[] =
    {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),

        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(0.6f, 0.6f, 0.6f),
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 0.5f, 0.0f),
    };

    float n = sqrtf(1.0f / 3), sz = 1.25f;
    glm::vec3 normal[] =
    {
        glm::vec3(-n, n, -n),
        glm::vec3(n, n, -n),
        glm::vec3(n, n, n),
        glm::vec3(-n, n, n),

        glm::vec3(-n, -n, -n),
        glm::vec3(n, -n, -n),
        glm::vec3(n, -n, n),
        glm::vec3(-n, -n, n),
    };

    std::vector<unsigned int> indeces;
    for (int j = 0; j < 24; j++) indeces.push_back(j);

    SetVertices({
            { glm::vec3(-sz, 0.0f, 0.0f), color[0], normal[0] },
            { glm::vec3(0.0f, sz, 0.0f), color[0], normal[0] },
            { glm::vec3(0.0f, 0.0f, -sz), color[0], normal[0] },

            { glm::vec3(0.0f, 0.0f, -sz), color[1], normal[1] },
            { glm::vec3(0.0f, sz, 0.0f), color[1], normal[1] },
            { glm::vec3(sz, 0.0f, 0.0f), color[1], normal[1] },

            { glm::vec3(sz, 0.0f, 0.0f), color[2], normal[2] },
            { glm::vec3(0.0f, sz, 0.0f), color[2], normal[2] },
            { glm::vec3(0.0f, 0.0f, sz), color[2], normal[2] },

            { glm::vec3(0.0f, 0.0f, sz), color[3], normal[3] },
            { glm::vec3(0.0f, sz, 0.0f), color[3], normal[3] },
            { glm::vec3(-sz, 0.0f, 0.0f), color[3], normal[3] },

            { glm::vec3(-sz, 0.0f, 0.0f), color[4], normal[4] },
            { glm::vec3(0.0f, 0.0f, -sz), color[4], normal[4] },
            { glm::vec3(0.0f, -sz, 0.0f), color[4], normal[4] },

            { glm::vec3(0.0f, 0.0f, -sz), color[5], normal[5] },
            { glm::vec3(sz, 0.0f, 0.0f), color[5], normal[5] },
            { glm::vec3(0.0f, -sz, 0.0f), color[5], normal[5] },

            { glm::vec3(sz, 0.0f, 0.0f), color[6], normal[6] },
            { glm::vec3(0.0f, 0.0f, sz), color[6], normal[6] },
            { glm::vec3(0.0f, -sz, 0.0f), color[6], normal[6] },

            { glm::vec3(0.0f, 0.0f, sz), color[7], normal[7] },
            { glm::vec3(-sz, 0.0f, 0.0f), color[7], normal[7] },
            { glm::vec3(0.0f, -sz, 0.0f), color[7], normal[7] },
        }, indeces, GL_STATIC_DRAW);
}
