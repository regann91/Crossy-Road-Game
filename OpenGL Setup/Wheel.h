#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "GameObject.h"

class Wheel : public GameObject {
public:

    Wheel() : GameObject() {}

    Wheel(float x, float y, float width, float height, std::string texPath);

    void draw() const override;

    void setPosition(float newX, float newY);

    float rotation;

    void rotate(float speed) override;
};