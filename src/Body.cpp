#include "Body.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Body::Body(){
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

    for (size_t i = 0; i < parts.size(); i++)
    {
        _bodyStack.push(parts[i]);
        _bodyStack.top()->draw(anim, ourShader, 0, 0);
        _bodyStack.pop();
        delete parts[i];
    }
}
