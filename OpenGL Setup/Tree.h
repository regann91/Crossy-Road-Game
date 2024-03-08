#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

#pragma once
#include "GameObject.h"

class Tree : public GameObject {
public:
    Tree(float x, float y, float width, float height);
    float getX() const;
    float getY() const;


    void draw() const override;

};
