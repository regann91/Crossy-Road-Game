#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include "Wheel.h"

#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:
    Wheel leftWheel;
    Wheel rightWheel;
    // Constructor
    MovingObject(float startX, float startY, float movingWidth, float movingHeight, glm::vec3 color, float movingSpeed);

    // Update function for car movement
    void update(float deltaTime);

    // Returns speed
    float getSpeed() const { return speed; }

private:
    float speed;
<<<<<<< HEAD:OpenGL Setup/Car.h

};
=======
};
>>>>>>> 6b28c0767d6546981ffcfe7c9411ff475020badf:OpenGL Setup/MovingObject.h
