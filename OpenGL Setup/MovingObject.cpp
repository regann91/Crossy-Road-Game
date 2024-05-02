#include "MovingObject.h"


MovingObject::MovingObject(float startX, float startY, float movingWidth, float movingHeight, std::string texPath, float movingSpeed, float laneW)
    : GameObject(startX, startY - movingHeight / 2, movingWidth, movingHeight, texPath), speed(movingSpeed), laneWidth(laneW) {}


// Update function implementation
void MovingObject::update(float deltaTime) {
    // Update the car position based on speed and elapsed time
    this->move(speed * deltaTime, 0);

    // Check if the car is out of the window, reset its position to the opposite side
    if (x > laneWidth / 2) {
        // Move to the left side
        this->setPosition(-laneWidth / 2, y);
    }
    else if (x < -laneWidth / 2) {
        // Move to the right side
        this->setPosition(laneWidth / 2, y);
    }
    // Update the wheel positions

    // Rotate the wheels
    float wheelRotationSpeed = speed * deltaTime * 360;  // Adjust this value as needed
}