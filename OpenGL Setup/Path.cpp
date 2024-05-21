#include "Path.h"
#include <algorithm>  // Include the algorithm header for std::shuffle
#include <random>     // Include the random header for std::default_random_engine

// Constructor implementation
Path::Path(float roadY, float roadZ, float roadWidth, glm::vec3 color, int nbObj, float objD)
    : GameObject(0, roadY, roadZ+50, roadWidth, 10, 100, color), nbObjPerLane(nbObj), objWidth(objD) {}

void Path::createRoadMovingObj(float initX, float initZ, float speed) {
    movingObjects.emplace_back(
        MovingObject(initX, 18, initZ, objWidth, 50.0, 50, glm::vec3(1, 0.96, 1), speed, width)
    );
    renderable->addChildRenderable(movingObjects.back().renderable);
}

void Path::createRiverMovingObj(float initX, float initZ, float speed) {
    movingObjects.emplace_back(
        MovingObject(initX, -11, initZ, objWidth, 20, 50.0, glm::vec3(1, 0.96, 1), speed, width)
    );
    renderable->addChildRenderable(movingObjects.back().renderable);
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

            // Create and setup new obj
            createRoadMovingObj(initialX, z + (50.0 * l), laneSpeed * std::pow(-1, l));
        }

        // Shuffle the objects in the lane to further randomize their positions
        auto lane_begin = movingObjects.begin() + l * nbObjPerLane;
        auto lane_end = movingObjects.begin() + (l + 1) * nbObjPerLane;
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
            createRiverMovingObj(initialX, z + (50.0 * l), laneSpeed * std::pow(-1, l));
        }

        // Shuffle the objects in the lane to further randomize their positions
        auto lane_begin = movingObjects.begin() + l * nbObjPerLane;
        auto lane_end = movingObjects.begin() + (l + 1) * nbObjPerLane;
        std::shuffle(lane_begin, lane_end, std::default_random_engine(std::random_device{}()));
    }
}

void Path::update(float deltaTime) {
    for (auto& obj : movingObjects) {
        obj.update(deltaTime * 0.001);  // Adjust the deltaTime as needed
    }
}

// Default behaviour
bool Path::getsKilled(std::shared_ptr<Character> player) {
    return false;
}