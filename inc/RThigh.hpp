#ifndef RTHIGH_H
#define RTHIGH_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Bodypart.hpp"
#include "RLowerPart.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::cout;

class RThigh : public Bodypart {
    private:
        void actualRender(void);
    public:
        RThigh(stack<Bodypart *> *bodyStack, Matrix model);
        ~RThigh();
        void draw(Animation &anim, Shader &ourShader, float x, float y);
        std::string _anim_key = std::string("a_rthigh");
};

#endif