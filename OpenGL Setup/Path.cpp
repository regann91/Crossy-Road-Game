#include "Path.h"
#include <algorithm>  // Include the algorithm header for std::shuffle
#include <random>     // Include the random header for std::default_random_engine

// Constructor implementation
Path::Path(float roadY, float roadWidth, std::string texPath, int nbObj, float objW) 
    : GameObject(0, roadY+50, roadWidth, 100, texPath), nbObjPerLane(nbObj), objWidth(objW) {}

// Override the draw function
void Path::draw() const {

    // Draw the path itself
    glColor4ub(255, 255, 255, 255);  // Set color to white
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2f(x - width / 2, y - height/2);
        glTexCoord2d(16.0, 0.0);
        glVertex2f(x + width / 2, y - height/2);
        glTexCoord2d(16.0, 1.0);
        glVertex2f(x + width / 2, y + height/2);
        glTexCoord2d(0.0, 1.0);
        glVertex2f(x - width / 2, y + height/2);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Draw all objects on it
    for (const auto& obj : RoadMovingObjects) {
        obj.draw();
    }
    for (const auto& obj : RiverMovingObjects) {
        obj.draw();
    }
}

RoadMovingObject Path::createRoadMovingObj(float initX, float initY, float speed) {
    return RoadMovingObject(initX, initY, objWidth, 50.0, "../OpenGL\ Setup/textures/car.bmp", speed, width, false);
}

RiverMovingObject Path::createRiverMovingObj(float initX, float initY, float speed) {
    return RiverMovingObject(initX, initY, objWidth, 50.0, "../OpenGL\ Setup/textures/trunk.bmp", speed, width);
}

void Path::initRoadMovingObjects() {
    const float baseSpacing = width / nbObjPerLane;  // Base spacing between cars

    // LANE GENERATION LOOP : 2 lanes
    for (int l = 0; l < 2; l++) {
        // Generate a single speed for the lane
        float laneSpeed = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 5.0 + 8.0;

        // Add cars to the road using randomized x positions and the same speed for the lane
        for (int i = 0; i < nbObjPerLane; ++i) {
            // Generate a random offset for the x position
            float offset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * baseSpacing - baseSpacing / 2;
            float initialX = i * baseSpacing + offset - width / 2; // Center on screen
            RoadMovingObjects.emplace_back(createRoadMovingObj(initialX, y + (50.0 * l), laneSpeed * std::pow(-1, l)));
        }

        // Shuffle the objects in the lane to further randomize their positions
        auto lane_begin = RoadMovingObjects.begin() + l * nbObjPerLane;
        auto lane_end = RoadMovingObjects.begin() + (l + 1) * nbObjPerLane;
        std::shuffle(lane_begin, lane_end, std::default_random_engine(std::random_device{}()));
    }
}

void Path::initRiverMovingObjects() {
    const float baseSpacing = width / nbObjPerLane;  // Base spacing between cars

    // LANE GENERATION LOOP : 2 lanes
    for (int l = 0; l < 2; l++) {
        // Generate a single speed for the lane
        float laneSpeed = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 5.0 + 8.0;

        // Add cars to the road using randomized x positions and the same speed for the lane
        for (int i = 0; i < nbObjPerLane; ++i) {
            // Generate a random offset for the x position
            float offset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * baseSpacing - baseSpacing / 2;
            float initialX = i * baseSpacing + offset - width / 2; // Center on screen
            RiverMovingObjects.emplace_back(createRiverMovingObj(initialX, y + (50.0 * l), laneSpeed * std::pow(-1, l)));
        }

        // Shuffle the objects in the lane to further randomize their positions
        auto lane_begin = RiverMovingObjects.begin() + l * nbObjPerLane;
        auto lane_end = RiverMovingObjects.begin() + (l + 1) * nbObjPerLane;
        std::shuffle(lane_begin, lane_end, std::default_random_engine(std::random_device{}()));
    }
}

void Path::update(float deltaTime) {
    for (auto& obj : RoadMovingObjects) {
        obj.update(deltaTime * 0.001);  // Adjust the deltaTime as needed
    }

    for (auto& obj : RiverMovingObjects) {
        obj.update(deltaTime * 0.001);  // Adjust the deltaTime as needed
    }
}

// Default behaviour
bool Path::getsKilled(Character* player) {
    return false;
}