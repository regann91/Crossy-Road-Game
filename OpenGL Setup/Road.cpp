#include "Road.h"
#include <random>

// Constructor
Road::Road(float riverY, float riverWidth)
    : Path(riverY, riverWidth, "../OpenGL\ Setup/textures/road.bmp", 5, 50) 
{
    initRoadMovingObjects();
}

// Generates a template moving object for the path
RoadMovingObject Road::createRoadMovingObj(float initX, float initY, float speed) {
    // Randomly decide whether to create a car or a truck
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    if (dis(gen) == 0) {
        // Create a car
        return RoadMovingObject(initX, initY, getObjWidth(), 50, "../OpenGL\ Setup/textures/car.bmp", speed, width, false);
    }
    else {
        // Create a truck
        return RoadMovingObject(initX, initY, getObjWidth(), 50, "../OpenGL\ Setup/textures/truck.bmp", speed, width, true);
    }
}

bool Road::getsKilled(Character* player) {
    // If player is on the road
    if(player->collidesWith(*this)) {
        // Check for collision with cars
        for (RoadMovingObject& obj : RoadMovingObjects) {
            if (player->collidesWith(obj)) return true;
        }
    }
    return false;
}