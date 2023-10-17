#ifndef LFOREARM_HPP
#define LFOREARM_HPP

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

class LForearm : public Bodypart {
    private:
        void actualRender(void);
    public:
        LForearm(stack<Bodypart *> *bodyStack, Matrix model);
        ~LForearm();
        void draw(Animation &anim, Shader &ourShader, float newx, float newy);
};

#endif