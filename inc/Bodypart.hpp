#ifndef BODYPART_H
#define BODYPART_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include "Animation.hpp"
#include "FtMath.hpp"
#include "Shader.hpp"

using std::stack;
using std::vector;
using std::cout;
using std::endl;

class Bodypart {
    protected:
        unsigned int VBO, VAO, EBO;
        stack<Bodypart *> *_bodyStack;
        virtual void actualRender() = 0;
    public:
        virtual ~Bodypart(){}
        virtual void draw(Animation &anim, Shader &ourShader) = 0;
};

#endif