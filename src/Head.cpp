#include "Head.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Head::Head(stack<Bodypart *> *bodyStack, Matrix model)
{
    _bodyStack = bodyStack;
    _model = model;
}

Head::~Head()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Head::draw(Animation &anim, Shader &ourShader, float newx, float newy)
{
    // model = frame["bp_1"] * model;
    ourShader.setMat4("model", _model);

    this->actualRender();
}

void Head::actualRender(void)
{
    float head[] =
        {
            0.5f, 1.75f, 0.1f,    // top right
            0.5f, 0.75f, 0.1f,   // bottom right
            -0.5f, 0.75f, 0.1f,  // bottom left
            -0.5f, 1.75f, 0.1f,   // top left
            -0.5f, 0.5f, -0.9f,  // top left behind
            0.5f, 0.5f, -0.9f,   // top right behind
            -0.5f, -0.5f, -0.9f, // bottom left behind
            0.5f, -0.5f, -0.9f   // bottom right behind
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(head), head, GL_STATIC_DRAW);

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