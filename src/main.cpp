#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <valarray>
#include <filesystem>
#include "Shader.h"
#include "color.h"
#include "Mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const GLfloat aspectRatio = 16.0f / 9.0f;
const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 450;

struct Point {
    float x, y;
    Point() : x(0), y(0) {}
} points;

GLint frameCount = 0;
GLfloat speed = 0.002f;

void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height)
{
    glViewport(0, 0, width, height);
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    int newHeight = static_cast<int>(width / aspectRatio);
    if (newHeight != height) {
        glfwSetWindowSize(window, width, newHeight);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        float x = (float)xpos / width * 2.0f - 1.0f;
        float y = -((float)ypos / height * 2.0f - 1.0f);

        points.x = x;
        points.y = y;
    }
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* initialize()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
//    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return window;
}

int main()
{
    std::cout << "Current Working Directory: "
              << std::filesystem::current_path()
              << std::endl;

    GLFWwindow* window = initialize();
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    if (!window) return -1;

    Shader wallShader("../../shaders/wall.vert", "../../shaders/wall.frag");
    Shader splashShader("../../shaders/splash.vert", "../../shaders/splash.frag");

    GLfloat wallVertices[] = {
        // positions          // texture coords
        1.0f,  1.0f, 0.0f,    1.0f, 1.0f,   // top right
        1.0f, -1.0f, 0.0f,    1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    GLuint wallIndices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    GLfloat splashVertices[] = {
        0.0f, 0.0f, 0.0f, static_cast<float>(SCR_WIDTH) / 2,
//        0.5f,  0.5f, 0.0f, static_cast<float>(SCR_WIDTH) / 2,
//        0.5f, -0.5f, 0.0f, static_cast<float>(SCR_WIDTH) / 2,
//        -0.5f, -0.5f, 0.0f, static_cast<float>(SCR_WIDTH) / 2,
//        -0.5f,  0.5f, 0.0f, static_cast<float>(SCR_WIDTH) / 2,
    };

    GLuint wallVBO, wallVAO, wallEBO;
    glGenVertexArrays(1, &wallVAO);
    glGenBuffers(1, &wallVBO);
    glGenBuffers(1, &wallEBO);

    glBindVertexArray(wallVAO);
    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wallEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wallIndices), wallIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    GLuint splashVBO, splashVAO;
    glGenVertexArrays(1, &splashVAO);
    glGenBuffers(1, &splashVBO);

    glBindVertexArray(splashVAO);
    glBindBuffer(GL_ARRAY_BUFFER, splashVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(splashVertices), splashVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    GLuint wallTexture;
    glGenTextures(1, &wallTexture);
    glBindTexture(GL_TEXTURE_2D, wallTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint wallWidth, wallHeight, wallChannels;
    GLubyte *wallData = stbi_load("../../textures/seamless_wall.jpg", &wallWidth, &wallHeight, &wallChannels, 0);
    if (wallData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallWidth, wallHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, wallData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(wallData);

    GLuint splashTexture;
    glGenTextures(1, &splashTexture);
    glBindTexture(GL_TEXTURE_2D, splashTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint splashWidth, splashHeight, splashChannels;
    GLubyte *splashData = stbi_load("../../textures/splash.png", &splashWidth, &splashHeight, &splashChannels, 0);
    if (splashData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, splashWidth, splashHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, splashData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(splashData);

    // uncomment this call to draw in wireframe polygons.
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        frameCount++;
        glClear(GL_COLOR_BUFFER_BIT);

        wallShader.use();
        glBindVertexArray(wallVAO);
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        glDrawElements(GL_TRIANGLES, sizeof(wallIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        splashShader.use();
        glBindVertexArray(splashVAO);
        glBindTexture(GL_TEXTURE_2D, splashTexture);

        // set splash size
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        float size = static_cast<float>(windowWidth) / 2;
        glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), sizeof(GLfloat), &size);
        float coord[] = {points.x, points.y};
        glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * sizeof(GLfloat), &coord);

        Color::RGB rgb = HSVtoRGB(Color::HSV {static_cast<float>(frameCount % 360), 0.5f, 0.5f});


//        rgb = Color::HSVtoRGB((Color::HSV {static_cast<float>((frameCount + 180) % 360), 0.5f, 0.5f}));
        glUniform3f(glGetUniformLocation(splashShader.ID, "splashColor"), rgb.r, rgb.g, rgb.b);
        glDrawArrays(GL_POINTS, 0, sizeof(splashVertices) / sizeof(GLfloat));


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &wallVAO);
    glad_glDeleteVertexArrays(1, &splashVAO);
    glDeleteBuffers(1, &wallVBO);
    glDeleteBuffers(1, &splashVBO);
    glDeleteBuffers(1, &wallEBO);

    glfwTerminate();
    return 0;
}


