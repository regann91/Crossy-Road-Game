#pragma once
#include "GameObject.h"

const int STEP = 25;

class Character : public GameObject {
public:
    // Speed at which the character moves
    float speed; 

    // Constructor
    Character(float startX = 0, float startY = 0);

    // Move the character based on keyboard input
    void move(float deltaX, float deltaY);
};