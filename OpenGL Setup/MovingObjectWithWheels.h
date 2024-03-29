#pragma once
#ifndef MOVING_OBJECT_WITH_WHEELS_H
#define MOVING_OBJECT_WITH_WHEELS_H

#include "MovingObject.h"
#include "Wheel.h"

class MovingObjectWithWheels : public MovingObject {
public:
    MovingObjectWithWheels(float startX, float startY, float movingWidth, float movingHeight, std::string texPath, float movingSpeed, float laneW);

    void draw() const;
    void update(float deltaTime);

private:
    Wheel leftWheel;
    Wheel rightWheel;
};

#endif 