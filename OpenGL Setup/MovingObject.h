#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:

    // Constructor
    MovingObject(float startX, float startY, float movingWidth, float movingHeight, glm::vec3 color, float movingSpeed);

    // Update function for car movement
    void update(float deltaTime);

    // Returns speed
    float getSpeed() const { return speed; }

private:
    float speed;
};