#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GameObject.h"

class Tree : public GameObject {
public:
    Tree(float x, float z, float width = 50.0, float height = 100.0, float depth = 50.0);
};