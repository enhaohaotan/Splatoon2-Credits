#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
    // the program ID
    GLuint ID;

    // constructor reads and builds the Shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader();
    // use/activate the Shader
    void use() const;
    // utility uniform functions
    void setUniform4f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
};


#endif //SHADER_H
