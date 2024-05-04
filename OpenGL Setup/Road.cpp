#include "Road.h"
#include <random>

// Constructor
Road::Road(float riverY, float riverWidth)
    : Path(riverY, riverWidth, glm::vec4(1, 0.68, 0.83, 1), 5, 50)
{
    initRoadMovingObjects();
}



bool Road::getsKilled(std::shared_ptr<Character> player) {
    // If player is on the road
    if(this->collidesWith(player)) {
        // Check for collision with cars
        for (auto& obj : movingObjects) {
            if (obj.collidesWith(player)) return true;
        }
    }
    return false;
}