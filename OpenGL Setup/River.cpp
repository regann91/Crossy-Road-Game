#include "River.h"

// Constructor
River::River(float riverY, float riverWidth) 
    : Path(riverY, riverWidth, "../OpenGL\ Setup/textures/river.bmp", 3, 120) 
{
    initRiverMovingObjects();
}

bool River::getsKilled(Character* player) {
    // If player is on the river
    if (player->collidesWith(*this)) {
        bool death = true;
        // Check for collision with trunks, which would keep player alive
        for (MovingObject& obj : movingObjects) {
            // If player is on trunk, then all good
            if (player->collidesWith(obj)) {
                death = false;
                //player->move(obj.getSpeed()*0.007,0);
                break;
            }
        }
        return death;
    }
    return false;
}