#include "River.h"

// Constructor
River::River(float riverY, float riverWidth) 
    : Path(riverY, riverWidth, "../OpenGL\ Setup/textures/river.bmp", 3, 120) 
{
    initMovingObjects();
}

// Generates a template moving object for the path
MovingObject River::createMovingObj(float initX, float initY, float speed) {
    return MovingObject(initX, initY, getObjWidth(), 50, "../OpenGL\ Setup/textures/trunk.bmp", speed, width);
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