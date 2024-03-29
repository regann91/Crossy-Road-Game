#pragma once
#include "Collectible.h"
#include "Character.h"

class Shoes : public Collectible {
public:
    // Constructor
    Shoes(float startX = 0, float startY = 0, float time = -1);

    // Override draw function
    void drawBar(Character* player) const;

    // Override collect function
    void tryCollect(Character* player) override;
};