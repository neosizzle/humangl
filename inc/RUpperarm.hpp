#ifndef RUPPERARM_H
#define RUPPERARM_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Bodypart.hpp"
#include "RForearm.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::cout;

class RUpperarm : public Bodypart {
    private:
        void actualRender(void);
    public:
        RUpperarm(stack<Bodypart *> *bodyStack, Matrix model);
        ~RUpperarm();
        void draw(Animation &anim, Shader &ourShader, float x, float y);
        std::string _anim_key = std::string("a_rupperarm");
};

#endif