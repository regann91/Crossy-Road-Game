#pragma once
#include "GameObject.h"

const int POS_OFFSET_MAX = 1;
const int ROT_OFFSET_MAX = 6;

class BodyPart : public GameObject {
public:
    // Constructor
    BodyPart(float startX = 0, float startY = 0, std::string texPath = "");

    // Function for drawing the object
    void draw() const override;

    // Animation loop
    virtual void update(float deltaTime, float newX, float newY, float speed);

    // x, y, rotation Offset
    float localPosX, localPosY, localRot;
    // Sign of offset in movement
    float movementOrient;
};