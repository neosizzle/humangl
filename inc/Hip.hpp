#ifndef HIP_H
#define HIP_H

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

class Hip {
    private:
        unsigned int VBO, VAO, EBO;
        void draw(void);
        void drawChestTest(void);
    public:
        Hip(stack<vector<float>> &stack);
        ~Hip();
        unsigned int getVAO();
};

#endif