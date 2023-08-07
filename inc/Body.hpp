#ifndef BODY_H
#define BODY_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using std::stack;
using std::vector;
using std::cout;

class Body {
    private:
        stack<vector<float>> _stack;
        unsigned int VBO, VAO, EBO;

    public:
        Body();
        ~Body();
        unsigned int getVAO();
};

#endif