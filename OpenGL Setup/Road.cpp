#include "Road.h"
#include <random>

// Constructor
Road::Road(float riverY, float riverWidth)
    : Path(riverY, riverWidth, "../OpenGL\ Setup/textures/road.bmp", 5, 50) 
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