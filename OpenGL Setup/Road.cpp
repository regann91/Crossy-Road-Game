#include "Road.h"
#include <random>

// Constructor
Road::Road(float riverZ, float riverWidth)
    : Path(-12, riverZ, riverWidth, glm::vec3(1, 0.68, 0.83), 5, 50)
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