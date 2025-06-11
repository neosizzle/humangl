#ifndef RFOREARM_HPP
#define RFOREARM_HPP

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

class RForearm : public Bodypart {
    private:
        void actualRender(void);
    public:
        RForearm(stack<Bodypart *> *bodyStack, Matrix model);
        ~RForearm();
        void draw(Animation &anim, Shader &ourShader, float newx, float newy);
        std::string _anim_key = std::string("a_rforearm");
};

#endif