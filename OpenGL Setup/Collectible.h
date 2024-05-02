#pragma once
#include "GameObject.h"
#include "Character.h"

class Collectible : public GameObject {
public:
    // Time the powerup will stay on screen/activated
    float time;
    // If the collectible is collected
    bool collected;

    // Spawn rate : lower is better
    static const float SPAWN_RATE;
    // Max time on screen/activated
    static const float MAX_TIME;

    // Constructor
    Collectible(float startX = 0, float startY = 0, float time = MAX_TIME, glm::vec4 color = glm::vec4(1));

    // Update function for time and collection
    void update(float deltaTime, Character* player);

    // Checks for collection
    virtual void tryCollect(Character* player);
};