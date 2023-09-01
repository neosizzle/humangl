#ifndef CHEST_H
#define CHEST_H

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

class Chest : public Bodypart {
    private:
        void actualRender(void);
    public:
        Chest(stack<Bodypart *> *bodyStack);
        ~Chest();
        void draw(void);
};

#endif