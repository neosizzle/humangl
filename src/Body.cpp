#include "Body.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Body::Body(){
    //Hip??
    // vector<float> hip =
    // {
    //     0.5f,  0.5f, 0.1f,  // top right
    //      0.5f, -0.5f, 0.1f,  // bottom right
    //     -0.5f, -0.5f, 0.1f,  // bottom left
    //     -0.5f,  0.5f, 0.1f,   // top left 
    //     -0.5f, 0.5f, -0.9f, // top left behind
    //     0.5f, 0.5f, -0.9f,   // top right behind
    //     -0.5f, -0.5f, -0.9f, // bottom left behind
    //     0.5f, -0.5f, -0.9f // bottom right behind
    // };

    // _stack.push(hip);
    // _stack.pop
    // MOVE THSE INTO THE DRAW FUNCTION
}

Body::~Body()
{
}

void Body::draw(Animation &anim, Shader &ourShader)
{

    Matrix model = Matrix(4, 1.0f); // make sure to initialize matrix to identity matrix first
    // We start from Hip
    vector<Bodypart *> parts =
    {
        new Hip(&_bodyStack, model)
    };

    for (int i = 0; i < parts.size(); i++)
    {
        _bodyStack.push(parts[i]);
        _bodyStack.top()->draw(anim, ourShader, 0, 0);
        _bodyStack.pop();
        delete parts[i];
    }
}

// void Body::actualDraw(unsigned int indices[], unsigned long indicesSize, size_t drawElementsLines)
// {
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);
//     // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//     glBindVertexArray(VAO);

//     float copiedBodyPart[_stack.top().size()];
//     copy(_stack.top().begin(), _stack.top().end(), copiedBodyPart);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(copiedBodyPart), copiedBodyPart, GL_STATIC_DRAW);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

// 	// unbind array now, rebind it later
//     glBindVertexArray(0); 

//     // uncomment this call to draw in wireframe polygons.
//     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
    
//     glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//         // glDrawArrays(GL_TRIANGLES, 0, 6);
//     glDrawElements(GL_TRIANGLES, drawElementsLines, GL_UNSIGNED_INT, 0);
// }

// Hip:draw{
//     while (i < 3)
//     {
//         stack.push(children[i]);
//         _stack.top().transformation();
//         _stack.top.draw();
//         _stack.pop();
//     }
//     _stack.push(lleg);
//     _stack.top.draw();
//     _stack.pop()

//     _stack.push(rleg);
//     _stack.top.draw();
//     _stack.pop();

//     _stack.push(torso);
//     _stack.top.draw();

//         _stack.push(larm);
//         _stack.top.draw();
//         _Stack.pop();

//         _stack.push(larm);
//         _stack.top.draw();
//         _Stack.pop();

//     _stack.pop();
// }

// lleg:draw{

// }

// void Body::hip(void)
// {
//     vector<float> hip =
//     {
//         0.5f,  0.5f, 0.1f,  // top right
//         0.5f, -0.5f, 0.1f,  // bottom right
//         -0.5f, -0.5f, 0.1f,  // bottom left
//         -0.5f,  0.5f, 0.1f,   // top left 
//         -0.5f, 0.5f, -0.9f, // top left behind
//         0.5f, 0.5f, -0.9f,   // top right behind
//         -0.5f, -0.5f, -0.9f, // bottom left behind
//         0.5f, -0.5f, -0.9f // bottom right behind
//     };
//     _stack.push(hip);
//     // _stack.top.draw(_stack);
//     // _stack.push(leftleg);
//     this->leftleg();

//     unsigned int indices[] = {  // note that we start from 0!
//         0, 1, 3,  // first Triangle
//         1, 2, 3,  // second Triangle
//         3, 4, 2,
//         0, 1, 5,
//         2, 6, 4,
//         1, 7, 5,
//         4, 5, 6,
//         7, 5, 6,
//         0, 3, 4,
//         4, 5, 0 
//     };
//     this->actualDraw(indices, sizeof(indices), 30);
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteBuffers(1, &EBO);
//     _stack.pop();
// }

// void Body::leftleg(void)
// {
//     vector<float> chest =
//         {
//             0.5f, 2.5f, 0.1f,    // top right
//             0.5f, 1.0f, 0.1f,   // bottom right
//             -0.5f, 1.0f, 0.1f,  // bottom left
//             -0.5f, 2.5f, 0.1f,   // top left
//             -0.5f, 0.5f, -0.9f,  // top left behind
//             0.5f, 0.5f, -0.9f,   // top right behind
//             -0.5f, -0.5f, -0.9f, // bottom left behind
//             0.5f, -0.5f, -0.9f   // bottom right behind
//         };

//     _stack.push(chest);

//     unsigned int indices[] = {         // note that we start from 0!
//         0, 1, 3, // first Triangle
//         1, 2, 3, // second Triangle
//     };
//     this->actualDraw(indices, sizeof(indices), 6);
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteBuffers(1, &EBO);
//     _stack.pop();
// }