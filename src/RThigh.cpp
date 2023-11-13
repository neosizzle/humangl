#include "RThigh.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

RThigh::RThigh(stack<Bodypart *> *bodyStack, Matrix model)
{
    _bodyStack = bodyStack;
    _model = model;
}

RThigh::~RThigh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void RThigh::draw(Animation &anim, Shader &ourShader, float newx, float newy)
{
    // _model = model * anim.get_current_frame()["bp_3"];
    ourShader.setMat4("model", _model);
    x = newx;
    y = newy;

    vector<Bodypart *> parts =
    {
        new RLowerPart(_bodyStack, _model)
    };
    for (int i = 0; i < parts.size(); i++)
    {
        _bodyStack->push(parts[i]);
        _bodyStack->top()->draw(anim, ourShader, x + 0.4f, y - .3125f);
        _bodyStack->pop();
        delete parts[i];
    }

    this->actualRender();
}

void RThigh::actualRender(void)
{
    float RThigh[] =
        {
            x + 0.5f,  y - .125f, 0.1f,  // top right
            x + 0.5f, y - .6125f, 0.1f,  // bottom right
            x + 0.3f, y - .6125f, 0.1f,  // bottom left
            x + 0.3f,  y - 0.125f, 0.1f,   // top left 

            x + 0.5f, y - .125f, -0.1f,   // top right behind
            x + 0.5f, y - .6125f, -0.1f, // bottom right behind
            x + 0.3f, y - .6125f, -0.1f, // bottom left behind
            x + 0.3f, y - .125f, -0.1f, // top left behind
        };

    unsigned int indices[] = {         // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3, // second Triangle
        2, 3, 7,
        2, 6, 7,
        4, 6, 7,
        4, 5, 6,
        0, 4, 5,
        0, 1, 5,
        0, 3, 4,
        4, 5, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(RThigh), RThigh, GL_STATIC_DRAW);

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
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
}