#ifndef LARM_H
#define LARM_H

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

class Larm : public Bodypart {
    private:
        void actualRender(void);
    public:
        Larm(stack<Bodypart *> *bodyStack);
        ~Larm();
        void draw(Animation &anim, Shader &ourShader);
};

#endif