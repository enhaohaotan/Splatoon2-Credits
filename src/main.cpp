#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <valarray>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include "color.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


const GLfloat aspectRatio = 9.0f / 16.0f;
const GLuint SCR_WIDTH = 1600;
const GLuint SCR_HEIGHT = 900;

struct Point {
    float x, y;
    Point() : x(0), y(0) {}
} points;

Color::RGB rgb;

GLint frameCount = 0;
GLint textureIndex = 0;
GLint frameIndex = 0;
GLfloat speed = 0.002f;

bool isLeftPressed, wasLeftPressed, isRightPressed, wasRightPressed = false;
GLint rightCount = 0;
GLint rightSpeed = 2;

int getRandomInteger(int min, int max) {
    static std::mt19937 engine(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine);
}

//void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height)
//{
//    glViewport(0, 0, width*2, height*2);
//}
//
//void window_size_callback(GLFWwindow* window, int width, int height) {
//    int newHeight = static_cast<int>(width / aspectRatio);
//    if (newHeight != height) {
//        glfwSetWindowSize(window, width, newHeight);
//    }
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
//    if ((button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) || button == GLFW_MOUSE_BUTTON_RIGHT) {
//        double xpos, ypos;
//        glfwGetCursorPos(window, &xpos, &ypos);
//
//        int width, height;
//        glfwGetWindowSize(window, &width, &height);
//
//        float x = (float)xpos / width * 2.0f - 1.0f;
//        float y = -((float)ypos / height * 2.0f - 1.0f) / 2;
//
//        points.x = x;
//        points.y = y;
//    }
//}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* initializeWindow()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Splatoon 2 Credits", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
//    glfwSetWindowSizeCallback(window, window_size_callback);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetMouseButtonCallback(window, mouse_button_callback);

//     glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}

void loadTexture(GLuint& texture, const GLchar* path)
{
//    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLint width, height, channels;
    GLubyte *data = stbi_load(path, &width, &height, &channels, 0);

    GLenum format;
    switch (channels) {
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: format = GL_RGB;  // Default fall-back
    }

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void loadShader(GLuint& shaderProgram, const GLchar *vertexPath, const GLchar *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);

    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// This VAO is a full screen overlay
void setWallVertices(GLuint& vbo, GLuint& ebo, GLuint& vao)
{
    GLfloat vertices[] = {
            // positions                     // texture coords
            1.0f,  1.0f, 0.0f,    1.0f, 1.0f,   // top right
            1.0f, -1.0f, 0.0f,    1.0f, 0.0f,   // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
            -1.0f,  1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    GLuint indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void setSplashVertices(GLuint& vbo, GLuint& vao)
{
    GLfloat vertices[] = {
            0.0f, 0.0f, 0.0f, static_cast<float>(SCR_WIDTH) / 2,
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

// This VAO is a half screen overlay in the center of the screen
void setFrameBufferVertices(GLuint& vbo, GLuint& ebo, GLuint& vao)
{
    GLfloat down = (1 - aspectRatio) / 2;
    GLfloat up = 1 - down;
    GLfloat vertices[] = {
            // positions                     // texture coords
            1.0f,  1.0f, 0.0f,    1.0f, up,   // top right
            1.0f, -1.0f, 0.0f,    1.0f, down,   // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, down,   // bottom left
            -1.0f,  1.0f, 0.0f,   0.0f, up    // top left
    };

    GLuint indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void setFrameBuffer(GLuint& fbo, GLuint& texture)
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT * 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_WIDTH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = {1.0f, 1.0f, 1.0f, 0.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void drawTexture()
{
//    GLint width = SCR_WIDTH, height = SCR_HEIGHT * 2;
    GLint width = SCR_WIDTH, height = SCR_WIDTH;

    glReadBuffer(GL_COLOR_ATTACHMENT0);
    std::vector<unsigned char> pixels(width * height * 4);

    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
}

int main()
{

    GLFWwindow* window = initializeWindow();

    if (!window) return -1;

    GLuint wallShader, splashShader;
    loadShader(wallShader, "../../shaders/wall.vert", "../../shaders/wall.frag");
    loadShader(splashShader, "../../shaders/splash.vert", "../../shaders/splash.frag");

    GLuint wallVBO, wallVAO, wallEBO;
    setWallVertices(wallVBO, wallEBO, wallVAO);

    GLuint fboVBO, fboVAO, fboEBO;
    setFrameBufferVertices(fboVBO, fboEBO, fboVAO);

    GLuint splashVBO, splashVAO;
    setSplashVertices(splashVBO, splashVAO);

    GLuint wallTexture;
    loadTexture(wallTexture, "../../textures/seamless_wall.jpg");

    GLuint splashTexture;
    loadTexture(splashTexture, "../../textures/splash.png");

    GLuint graffitiTexture;
    loadTexture(graffitiTexture, "../../textures/graffiti4.png");

    GLuint smallSplashTexture[14];
    for (int i = 0; i < 14; ++i)
    {
        std::string path = "../../textures/splash" + std::to_string(i) + ".png";
        loadTexture(smallSplashTexture[i], path.c_str());
    }

    GLuint fbo[2];
    GLuint fboTexture[2];
    setFrameBuffer(fbo[0], fboTexture[0]);
    setFrameBuffer(fbo[1], fboTexture[1]);

    // render initial empty wall
    glBindFramebuffer(GL_FRAMEBUFFER, fbo[frameIndex]);
//    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT * 2);
    glViewport(0, 0, SCR_WIDTH, SCR_WIDTH);
    glUseProgram(wallShader);
    glBindVertexArray(wallVAO);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // render loop
    // -----------

    while(!glfwWindowShouldClose(window))
    {
        frameCount++;
        processInput(window);
        // render last frame into current window
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(wallShader);
        glUniform1f(glGetUniformLocation(wallShader, "offsetY"), 0);
        glBindTexture(GL_TEXTURE_2D, fboTexture[frameIndex]);
        glBindVertexArray(fboVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // render current frame into frame buffer
        frameIndex = frameIndex == 1 ? 0 : 1;
        glBindFramebuffer(GL_FRAMEBUFFER, fbo[frameIndex]);
//        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT * 2);
        glViewport(0, 0, SCR_WIDTH, SCR_WIDTH);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(wallShader);
        glUniform1f(glGetUniformLocation(wallShader, "offsetY"), static_cast<float>(frameCount) * speed);
//        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glBindVertexArray(wallVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glUniform1f(glGetUniformLocation(wallShader, "offsetY"), speed);
        frameIndex = frameIndex == 1 ? 0 : 1;
        glBindTexture(GL_TEXTURE_2D, fboTexture[frameIndex]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        frameIndex = frameIndex == 1 ? 0 : 1;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
            rightCount = 0;
        }
        isLeftPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
        isRightPressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

        if (isRightPressed) {
            rightCount = (rightCount + 1) % rightSpeed;
        }

        if ((isLeftPressed && !wasLeftPressed) || (isRightPressed && rightCount == 1))
        {

            glUseProgram(splashShader);
            glActiveTexture(GL_TEXTURE0);
            if (isRightPressed) {
                rgb = HSVtoRGB(Color::HSV {static_cast<float>((frameCount + 180 * 3) % (360 * 3)) / 3, 0.6f, 0.8f});
                GLint index = getRandomInteger(0, 13);
                glBindTexture(GL_TEXTURE_2D, smallSplashTexture[index]);
            }
            else {
                rgb = HSVtoRGB(Color::HSV {static_cast<float>(frameCount % (360 * 3)) / 3, 0.6f, 0.8f});
                glBindTexture(GL_TEXTURE_2D, splashTexture);
            }

            glUniform1i(glGetUniformLocation(splashShader, "splashSampler"), 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, graffitiTexture);
            glUniform1i(glGetUniformLocation(splashShader, "graffitiSampler"), 1);
            glActiveTexture(GL_TEXTURE0);
            glUniform1f(glGetUniformLocation(splashShader, "offsetY"), static_cast<float>(frameCount) * speed);

            // update coordinates
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            int width, height;
            glfwGetWindowSize(window, &width, &height);

            float x = (float)xpos / width * 2.0f - 1.0f;
            float y = -((float)ypos / height * 2.0f - 1.0f) / 2;

            points.x = x;
            points.y = y;

            // set splash position
            float coord[] = {points.x, points.y};
//            std::cout << points.x << " " << points.y << std::endl;
            glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * sizeof(GLfloat), &coord);



            glUniform3f(glGetUniformLocation(splashShader, "splashColor"), rgb.r, rgb.g, rgb.b);
            glBindVertexArray(splashVAO);
            glDrawArrays(GL_POINTS, 0, 4);
        }
        wasLeftPressed = isLeftPressed;
        wasRightPressed = isRightPressed;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

//    glDeleteVertexArrays(1, &wallVAO);
//    glDeleteVertexArrays(1, &splashVAO);
//    glDeleteBuffers(1, &wallVBO);
//    glDeleteBuffers(1, &splashVBO);
//    glDeleteBuffers(1, &wallEBO);


    glfwTerminate();
    return 0;
}


