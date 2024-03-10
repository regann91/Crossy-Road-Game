#include "MovingObject.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

// Constructor implementation
MovingObject::MovingObject(float startX, float startY, float carWidth, float carHeight, glm::vec3 color, float carSpeed)
    : GameObject(startX, startY, carWidth, carHeight, color), speed(carSpeed) {}

// Update function implementation
void MovingObject::update(float deltaTime) {
    // Update the car position based on speed and elapsed time
    x += speed * deltaTime;

    // Check if the car is out of the window, reset its position to the opposite side
    if (x > 800) {
        x = -width;  // Move to the left side
    }
    else if (x < -width) {
        x = 800;  // Move to the right side
    }
}