#ifndef MESH_H
#define MESH_H


#include <glad/glad.h>
#include <vector>

class Mesh
{
public:
//    GLuint VAO, VBO, EBO;

    Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint> &indices);
    Mesh(const std::vector<GLfloat>& vertices);
    ~Mesh();

private:
    GLuint VAO, VBO, EBO;

    void initializeVAO();
    void initializeVBO(const std::vector<GLfloat> &vertices);
    void initializeEBO(const std::vector<GLuint> &indices);
//    int count;
};


#endif //MESH_H
