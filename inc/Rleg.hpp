#ifndef RLEG_H
#define RLEG_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Bodypart.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::cout;

class Rleg : public Bodypart {
    private:
        void actualRender(void);
    public:
        Rleg(stack<Bodypart *> *bodyStack, Matrix model);
        ~Rleg();
        void draw(Animation &anim, Shader &ourShader, float x, float y);
};

#endif