#ifndef HIP_H
#define HIP_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Bodypart.hpp"
#include "Chest.hpp"
#include "LThigh.hpp"
#include "RThigh.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::cout;

class Hip : public Bodypart {
    private:
        void actualRender();
        // timing
    public:
        Hip(stack<Bodypart *> *bodyStack, Matrix model);
        ~Hip();
        void draw(Animation &anim, Shader &ourShader, float x, float y);
};

#endif