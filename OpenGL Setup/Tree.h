#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GameObject.h"

class Tree : public GameObject {
public:
    Tree(float x, float y, float width = 50.0, float height = 50.0);
};