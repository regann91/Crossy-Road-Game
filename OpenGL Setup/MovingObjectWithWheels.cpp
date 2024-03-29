#include "MovingObjectWithWheels.h"

MovingObjectWithWheels::MovingObjectWithWheels(float startX, float startY, float movingWidth, float movingHeight, std::string texPath, float movingSpeed, float laneW)
    : MovingObject(startX, startY, movingWidth, movingHeight, texPath, movingSpeed, laneW),
    leftWheel(startX - movingWidth / 2 + 12, startY - movingHeight / 2 + 10, 15, 15),
    rightWheel(startX + movingWidth / 2 - 12, startY - movingHeight / 2 + 10, 15, 15) {}

void MovingObjectWithWheels::draw() const {
    MovingObject::draw();  // Draw the moving object
    leftWheel.draw();  // Draw the left wheel
    rightWheel.draw();  // Draw the right wheel
}

void MovingObjectWithWheels::update(float deltaTime) {
    MovingObject::update(deltaTime);  // Update the moving object
    leftWheel.setPosition(x - width / 2 + 12, y - height / 2 + 10);
    rightWheel.setPosition(x + width / 2 - 12, y - height / 2 + 10);
    leftWheel.rotate(getSpeed());
    rightWheel.rotate(getSpeed());
}