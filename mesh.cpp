#include "mesh.h"

//finalize creation of model
void Mesh::SetVertices(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indeces, unsigned int isStatic)
{
    //destroy buffers
    if (m_created)
        glDeleteVertexArrays(1, &m_vertexData);

    m_created = true;

    //create vertex buffer
    glGenVertexArrays(1, &m_vertexData);
    glBindVertexArray(m_vertexData);

    //split into buffers
    glGenBuffers(VB_COUNT, m_buffers);

    //write data
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), (const void*)&vertices[0], isStatic);

    //set data types
    {
        //positions
        glEnableVertexAttribArray(VB_POS);
        glVertexAttribPointer(VB_POS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        //colors
        glEnableVertexAttribArray(VB_COLOR);
        glVertexAttribPointer(VB_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));

        //normals
        glEnableVertexAttribArray(VB_NORMAL);
        glVertexAttribPointer(VB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(glm::vec3)));
    }

    //set indeces
    glGenBuffers(1, &m_indeces);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indeces);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeces.size() * sizeof(unsigned int), (const void*)&indeces[0], isStatic);

    //unbind buffer
    glBindVertexArray(0);

    //set draw count
    m_drawCount = indeces.size();
}

//clear memory
Mesh::~Mesh()
{
    //destroy buffers
    if (m_created)
        glDeleteVertexArrays(1, &m_vertexData);
}

//draw mesh
void Mesh::Draw()
{
    //bind buffer
    glBindVertexArray(m_vertexData);

    //send data
    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, nullptr);

    //unbind buffers
    glBindVertexArray(0);
}
