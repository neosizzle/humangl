#include "Lleg.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Lleg::Lleg(stack<Bodypart *> *bodyStack)
{
    _bodyStack = bodyStack;
}

Lleg::~Lleg()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Lleg::draw(Animation &anim, Shader &ourShader)
{
    Matrix model = Matrix(4, 1.0f); // make sure to initialize matrix to identity matrix first
    // model = anim.get_current_frame()["bp_1"] * model;
    ourShader.setMat4("model", model);

    this->actualRender();
}

void Lleg::actualRender(void)
{
    float lleg[] =
        {
            -0.3f,  -0.5f, 0.1f,  // top right
            -0.3f, -1.5f, 0.1f,  // bottom right
            -0.5f, -1.5f, 0.1f,  // bottom left
            -0.5f,  -0.5f, 0.1f,   // top left 
            -0.5f, 0.5f, -0.9f, // top left behind
            0.5f, 0.5f, -0.9f,   // top right behind
            -0.5f, -0.5f, -0.9f, // bottom left behind
            0.5f, -0.5f, -0.9f // bottom right behind
        };

    unsigned int indices[] = {         // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3, // second Triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lleg), lleg, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	// unbind array now, rebind it later
    glBindVertexArray(0); 

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}