#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates for a cube
GLfloat vertices[] = {
    //     COORDINATES     /        COLORS      /   TexCoord  //
    // Front face
    -0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,     0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 1.0f,

    // Back face
    -0.5f, -0.5f, -0.5f,     0.92f, 0.86f, 0.76f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,     0.92f, 0.86f, 0.76f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,  0.0f, 1.0f,

    // Left face
    -0.5f,  0.5f,  0.5f,     0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,     0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,

    // Right face
     0.5f,  0.5f,  0.5f,     0.92f, 0.86f, 0.76f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,     0.92f, 0.86f, 0.76f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,     0.92f, 0.86f, 0.76f,  0.0f, 0.0f,

     // Top face
     -0.5f,  0.5f,  0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 1.0f,
      0.5f,  0.5f,  0.5f,     0.83f, 0.70f, 0.44f,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,     0.83f, 0.70f, 0.44f,  1.0f, 0.0f,
     -0.5f,  0.5f, -0.5f,     0.83f, 0.70f, 0.44f,  0.0f, 0.0f,

     // Bottom face
     -0.5f, -0.5f,  0.5f,     0.92f, 0.86f, 0.76f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,     0.92f, 0.86f, 0.76f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,     0.92f, 0.86f, 0.76f,  1.0f, 0.0f,
     -0.5f, -0.5f, -0.5f,     0.92f, 0.86f, 0.76f,  0.0f, 0.0f,
};

// Indices for vertices order
GLuint indices[] = {
    0,  1,  2,  0,  2,  3,  // Front face
    4,  5,  6,  4,  6,  7,  // Back face
    8,  9, 10,  8, 10, 11,  // Left face
    12, 13, 14, 12, 14, 15, // Right face
    16, 17, 18, 16, 18, 19, // Top face
    20, 21, 22, 20, 22, 23  // Bottom face
};

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(width, height, "Mimo", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load GLAD
    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, width, height);

    // Shader
    Shader shaderProgram("default.vert", "default.frag");

    // VAO, VBO, EBO
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // Link VBO attributes
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Texture
    Texture brickTex("./brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    brickTex.texUnit(shaderProgram, "tex0", 0);

    // Depth test
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        // Clear buffers
        glClearColor(1.0f, 0.71f, 0.76f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader program
        shaderProgram.Activate();

        // Transformations
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

        // Bind texture and VAO
        brickTex.Bind();
        VAO1.Bind();

        // Draw cube
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    brickTex.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}