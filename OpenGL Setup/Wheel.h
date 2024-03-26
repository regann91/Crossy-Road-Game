#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "GameObject.h"


class Wheel : public GameObject {
public:

    Wheel(float startX, float startY, float wheelWidth, float wheelHeight, float radius, float angle, float speed);

    void rotate(float deltaTime);

    void draw(float x, float y) const;

private:
    float radius;
    float angle;
    float speed;
};

