#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

#include "GameObject.h"

class Tree : public GameObject {
public:
    Tree(float x, float y, float width, float height);
    float getX() const;
    float getY() const;
};