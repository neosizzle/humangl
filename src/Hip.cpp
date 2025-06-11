#include "Hip.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Hip::Hip(stack<Bodypart *> *bodyStack, Matrix model)
{
    _bodyStack = bodyStack;
    _model = model;
}

Hip::~Hip()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Hip::draw(Animation &anim, Shader &ourShader, float x, float y)
{
    // calculate the model matrix for each object and pass it to shader before drawing
    // Matrix model = Matrix(4, 1.0f); // make sure to initialize matrix to identity matrix first
    // apply animations
    // _model = anim.get_current_frame()["bp_1"];

    std::map<std::string, Matrix> frame = anim.get_current_frame();
    if (frame.count(_anim_key))
        _model = frame[_anim_key] * _model;

    vector<Bodypart *> parts =
    {
        new Chest(_bodyStack, _model),
        new LThigh(_bodyStack, _model),
        new RThigh(_bodyStack, _model)
    };
    for (int i = 0; i < parts.size(); i++)
    {
        _bodyStack->push(parts[i]);
        _bodyStack->top()->draw(anim, ourShader, 0.0f, -0.375f);
        _bodyStack->pop();
        delete parts[i];
    }

    // std::cout << model.to_string() << "\n";
    ourShader.setMat4("model", _model);
    this->actualRender();
}

void Hip::actualRender()
{
    float hip[] =
        {
            0.5f,  -0.25f, 0.1f,  // top right
            0.5f, -0.5, 0.1f,  // bottom right
            -0.5f, -0.5f, 0.1f,  // bottom left
            -0.5f, -0.25f, 0.1f,   // top left 
            -0.5f, -0.25f, -0.4f, // top left behind
            0.5f, -0.25f, -0.4f,   // top right behind
            -0.5f, -0.5f, -0.4f, // bottom left behind
            0.5f, -0.5f, -0.4f // bottom right behind
        };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,  // second Triangle
        3, 4, 2,
        0, 1, 5,
        2, 6, 4,
        1, 7, 5,
        4, 5, 6,
        7, 5, 6,
        0, 3, 4,
        4, 5, 0 
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hip), hip, GL_STATIC_DRAW);

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