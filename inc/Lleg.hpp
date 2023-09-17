#ifndef LLEG_H
#define LLEG_H

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

class Lleg : public Bodypart {
    private:
        void actualRender(void);
    public:
        Lleg(stack<Bodypart *> *bodyStack);
        ~Lleg();
        void draw(Animation &anim, Shader &ourShader);
};

#endif