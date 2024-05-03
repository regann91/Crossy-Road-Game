#include "MovingObject.h"


MovingObject::MovingObject(float startX, float startY, float startZ, float movingWidth, float movingHeight, float movingDepth, glm::vec4 color, float movingSpeed, float laneW)
    : GameObject(startX, startY, startZ - movingDepth / 2, movingWidth, movingHeight, movingDepth, color), speed(movingSpeed), laneWidth(laneW) {}


// Update function implementation
void MovingObject::update(float deltaTime) {
    // Update the car position based on speed and elapsed time
    this->move(speed * deltaTime, 0, 0);

    // Check if the car is out of the window, reset its position to the opposite side
    if (x > laneWidth / 2) {
        // Move to the left side
        this->setPosition(-laneWidth / 2, y, z);
        this->renderable->scale(-1, 0, 0);
    }
    else if (x < -laneWidth / 2) {
        // Move to the right side
        this->setPosition(laneWidth / 2, y, z);
        this->renderable->scale(-1, 0, 0);
    }
    // Update the wheel positions

    // Rotate the wheels
    float wheelRotationSpeed = speed * deltaTime * 360;  // Adjust this value as needed
}