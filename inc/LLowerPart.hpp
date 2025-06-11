#ifndef LLOWERPART
#define LLOWERPART

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

class LLowerPart : public Bodypart {
    private:
        void actualRender(void);
    public:
        LLowerPart(stack<Bodypart *> *bodyStack, Matrix model);
        ~LLowerPart();
        void draw(Animation &anim, Shader &ourShader, float newx, float newy);
        std::string _anim_key = std::string("a_llowerpart");

};

#endif