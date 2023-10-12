#ifndef HEAD_H
#define HEAD_H

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

class Head : public Bodypart {
    private:
        void actualRender(void);
    public:
        Head(stack<Bodypart *> *bodyStack, Matrix model);
        ~Head();
        void draw(Animation &anim, Shader &ourShader, float newx, float newy);
};

#endif