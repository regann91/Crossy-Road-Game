#include "River.h"

// Constructor
River::River(float riverZ, float riverWidth) 
    : Path(-22, riverZ, riverWidth, glm::vec3(0.5, 0.85, 1), 3, 120, "riverTex.bmp")
{
    initRiverMovingObjects();
}

bool River::getsKilled(std::shared_ptr<Character> player) {
    // If player is on the river
    if (this->collidesWith(player)) {
        bool death = true;
        // Check for collision with trunks, which would keep player alive
        for (MovingObject& obj : movingObjects) {
            // If player is on trunk, then all good
            if (obj.collidesWith(player)) {
                death = false;
                //player->move(obj.getSpeed()*0.007,0);
                break;
            }
        }
        return death;
    }
    return false;
}