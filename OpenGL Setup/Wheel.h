#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GameObject.h"

class Wheel : public GameObject {
public:
    Wheel(float x, float y, float width, float height);

    void draw() const;

    void setPosition(float newX, float newY);

    void rotate(float speed);

    float rotation;
};