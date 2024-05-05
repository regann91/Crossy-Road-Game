#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:
    // Constructor
    MovingObject(float startX, float startY, float startZ, 
        float movingWidth, float movingHeight, float movingDepth, 
        glm::vec4 color, float movingSpeed, float laneW);

    // Update function for movement
    void update(float deltaTime);

    // Returns speed
    float getSpeed() const { return speed; }

private:
    // Speed of moving object
    float speed;
    // Width of the lane it is on
    float laneWidth;
};
