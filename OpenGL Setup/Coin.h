#pragma once
#include "Collectible.h"

class Coin : public Collectible {
public:
    // Constructor
    Coin(float startX = 0, float startY = 0, float time = -1);
};