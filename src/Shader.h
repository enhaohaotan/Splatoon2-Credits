#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h> // include glad to get all the required OpenGL headers

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
//    void setBool1(const std::string &name, bool v0) const;
//    void setInt1(const std::string &name, int v0) const;
//    void setFloat1(const std::string &name, float v0) const;
    void setUniform4f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
};


#endif //SHADER_H
