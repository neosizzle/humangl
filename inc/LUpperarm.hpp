#ifndef LUPPERARM_H
#define LUPPERARM_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Bodypart.hpp"
#include "LForearm.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::cout;

class LUpperarm : public Bodypart {
    private:
        void actualRender(void);
    public:
        LUpperarm(stack<Bodypart *> *bodyStack, Matrix model);
        ~LUpperarm();
        void draw(Animation &anim, Shader &ourShader, float newx, float newy);
};

#endif