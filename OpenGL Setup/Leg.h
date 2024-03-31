#pragma once
#include "BodyPart.h"

const int LEG_OFFSET_MAX = 2;

class Leg : public BodyPart {
public:
    // Constructor
    Leg(float startX = 0, float startY = 0, bool isLeftLeg = true);

    // Custom animation
    void update(float deltaTime, float newX, float newY, float speed) override;
};