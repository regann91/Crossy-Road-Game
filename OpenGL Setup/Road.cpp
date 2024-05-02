#include "Road.h"
#include <random>

// Constructor
Road::Road(float riverY, float riverWidth)
    : Path(riverY, riverWidth, glm::vec4(0.65, 0.55, 0.5, 1), 5, 50)
{
    initRoadMovingObjects();
}



bool Road::getsKilled(Character* player) {
    // If player is on the road
    if(player->collidesWith(*this)) {
        // Check for collision with cars
        for (auto& obj : movingObjects) {
            if (player->collidesWith(obj)) return true;
        }
    }
    return false;
}