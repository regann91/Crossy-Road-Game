#include "GameObject.h"
#include "Character.h"

class Shoes : public GameObject {
public:
    // If the power up shoes are activated
    bool activated;
    // Time the powerup will stay on screen/activated
    float time;

    // Spawn rate : lower is better
    static const float SPAWN_RATE;
    // Max time on screen/activated
    static const float MAX_TIME;

    // Constructor
    Shoes(float startX = 0, float startY = 0, float time = -1);

    // Override draw function
    void drawBar(Character* player) const;

    // Update function for time and activation
    void update(float deltaTime, Character* player);
};