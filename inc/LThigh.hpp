#ifndef LTHIGH_H
#define LTHIGH_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Bodypart.hpp"
#include "LLowerPart.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::cout;

class LThigh : public Bodypart {
    private:
        void actualRender(void);
    public:
        LThigh(stack<Bodypart *> *bodyStack, Matrix model);
        ~LThigh();
        void draw(Animation &anim, Shader &ourShader, float newx, float newy);
        std::string _anim_key = std::string("a_ltigh");

};

#endif