#include "Road.h"
#include <random>

// Constructor
Road::Road(float riverY, float riverWidth)
    : Path(riverY, riverWidth, "../OpenGL\ Setup/textures/road.bmp", 5, 50) 
{
    initMovingObjects();
}

// Generates a template moving object for the path
MovingObject Road::createMovingObj(float initX, float initY, float speed) {
    // Randomly decide whether to create a car or a truck
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    if (dis(gen) == 0) {
        // Create a car
        return MovingObject(initX, initY, getObjWidth(), 50, "../OpenGL\ Setup/textures/car.bmp", speed, width);
    }
    else {
        // Create a truck
        return MovingObject(initX, initY, getObjWidth(), 50, "../OpenGL\ Setup/textures/truck.bmp", speed, width);
    }
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