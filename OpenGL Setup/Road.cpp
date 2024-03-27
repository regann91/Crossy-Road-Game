#include "Road.h"

// Constructor
Road::Road(float riverY, float riverWidth)
    : Path(riverY, riverWidth, "../OpenGL\ Setup/textures/road.bmp", 5, 50) 
{
    initMovingObjects();
}

// Generates a template moving object for the path
MovingObject Road::createMovingObj(float initX, float initY, float speed) {
    return MovingObject(initX, initY, getObjWidth(), 50, "../OpenGL\ Setup/textures/car.bmp", speed, width);
}

bool Road::getsKilled(Character* player) {
    // If player is on the road
    if(player->collidesWith(*this)) {
        // Check for collision with cars
        for (MovingObject& obj : movingObjects) {
            if (player->collidesWith(obj)) return true;
        }
    }
    return false;
}