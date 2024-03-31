#pragma once
#include "GameObject.h"
#include "Leg.h"
#include "Arm.h"

const int STEP = 25;

class Character : public GameObject {
public:
    // Speed at which the character moves
    float speed; 

    // Constructor
    Character(float startX = 0, float startY = 0);

    // Move the character based on keyboard input
    void move(float deltaX, float deltaY);

    // Function for drawing the object
    void draw() const override;

    // Update loop animation
    void update(float deltaTime);

private:
    // Body parts
    GameObject backpack;
    BodyPart head;
    Leg legL;
    Leg legR;
    Arm armL;
    Arm armR;
};