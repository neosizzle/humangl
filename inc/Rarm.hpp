#ifndef RARM_H
#define RARM_H

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

class Rarm : public Bodypart {
    private:
        void actualRender(void);
    public:
        Rarm(stack<Bodypart *> *bodyStack);
        ~Rarm();
        void draw(void);
};

#endif