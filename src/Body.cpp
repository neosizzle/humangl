#include "Body.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Body::Body(){
    float vertices[] = {
         0.5f,  0.5f, 0.1f,  // top right
         0.5f, -0.5f, 0.1f,  // bottom right
        -0.5f, -0.5f, 0.1f,  // bottom left
        -0.5f,  0.5f, 0.1f,   // top left 
        -0.5f, 0.5f, -0.9f, // top left behind
        0.5f, 0.5f, -0.9f,   // top right behind
        -0.5f, -0.5f, -0.9f, // bottom left behind
        0.5f, -0.5f, -0.9f // bottom right behind
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,  // second Triangle
        3, 4, 2,
        0, 1, 5,
        2, 6, 4,
        1, 7, 5
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

Body::~Body()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

unsigned int Body::getVAO()
{
    return (VAO);
}