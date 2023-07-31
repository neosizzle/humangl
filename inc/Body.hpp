#ifndef BODY_H
#define BODY_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <string>
#include <map>
#include <vector>

class Body {
    private:
        unsigned int VBO, VAO, EBO;
    public:
        Body();
        ~Body();
        unsigned int getVAO();
};

#endif