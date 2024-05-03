#pragma once
#include "GameObject.h"

const int STEP = 25;

class Character : public GameObject {
public:
    // Speed at which the character moves
    float speed; 

    // Constructor
    Character(float startX = 0, float startZ = 0);

    void move(float dx, float dy, float dz);
};