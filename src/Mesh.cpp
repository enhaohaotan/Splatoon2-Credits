#include "Mesh.h"

Mesh::Mesh(const std::vector<GLfloat> &vertices, const std::vector<GLuint> &indices)
{
    initializeVAO();
    initializeVBO(vertices);
    initializeEBO(indices);
}

Mesh::Mesh(const std::vector<GLfloat>& vertices)
{
    initializeVAO();
    initializeVBO(vertices);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::initializeVAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void Mesh::initializeVBO(const std::vector<GLfloat> &vertices)
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
}

void Mesh::initializeEBO(const std::vector<GLuint> &indices)
{
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}