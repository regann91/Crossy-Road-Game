#pragma once
#include "GameObject.h"

class RiverMovingObject : public GameObject {
public:
    // Constructor
    RiverMovingObject(float startX, float startY, float movingWidth, float movingHeight, std::string texPath, float movingSpeed, float laneW);

    // Override draw function
    void draw() const override;

    // Update function for car movement
    void update(float deltaTime);

    // Returns speed
    float getSpeed() const { return speed; }

private:
    // Speed of moving object
    float speed;
    // Width of the lane it is on
    float laneWidth;
};