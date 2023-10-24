#ifndef RLOWERPART
#define RLOWERPART

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

class RLowerPart : public Bodypart {
    private:
        void actualRender(void);
    public:
        RLowerPart(stack<Bodypart *> *bodyStack, Matrix model);
        ~RLowerPart();
        void draw(Animation &anim, Shader &ourShader, float newx, float newy);
};

#endif