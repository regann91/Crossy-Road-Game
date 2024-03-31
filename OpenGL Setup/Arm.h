#pragma once
#include "BodyPart.h"

class Arm : public BodyPart {
public:
    // Constructor
    Arm(float startX = 0, float startY = 0, bool isLeftArm = true);

    void update(float deltaTime, float newX, float newY, float speed) override;
};