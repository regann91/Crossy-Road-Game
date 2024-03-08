#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

#pragma once
#include "GameObject.h"

class Car : public GameObject {
public:

    // Constructor
    Car(float startX, float startY, float carWidth, float carHeight, float carSpeed);

    // Update function for car movement
    void update(float deltaTime);

    // Override the draw function
    void draw() const override;

private:
    float speed;
};
