#ifndef BODY_H
#define BODY_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Bodypart.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>

#include "Hip.hpp"
#include "Animation.hpp"
#include "FtMath.hpp"
#include "Shader.hpp"

using std::stack;
using std::vector;
using std::cout;
using std::endl;

class Body {
    private:
        stack<Bodypart *> _bodyStack;
    public:
        Body();
        ~Body();
        void draw(Animation &anim, Shader &ourShader);
};

#endif