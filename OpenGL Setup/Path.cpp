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
    for (const auto& obj : movingObjects) {
        obj.draw();
    }
}

MovingObject Path::createMovingObj(float initX, float initY, float speed) {
    return MovingObject(initX, initY, objWidth, 50.0, "../OpenGL\ Setup/textures/car.bmp", speed, width);
}

void Path::initMovingObjects() {
    const float spacing = width / nbObjPerLane;
    const float objSpacing = 30;  // Ensure at least 30.0 spacing between cars

    std::vector<float> xPositions;
    // LANE GENERATION LOOP : 2 lanes
    for (int l = 0; l < 2; l++) {
        // Repeat the process for the second lane
        xPositions.clear();  // Clear the vector for the next set of x positions

        // Generate initial x positions with a larger range
        for (int i = 0; i < nbObjPerLane; ++i) {
            xPositions.push_back(i * spacing + (rand() % static_cast<int>(width)));
        }

        // Shuffle the x positions randomly
        std::shuffle(xPositions.begin(), xPositions.end(), std::default_random_engine(std::random_device{}()));

        // Generate a single speed for the lane
        float laneSpeed = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 4.0 + 2;

        // Add cars to the road using randomized x positions and the same speed for the lane
        for (int i = 0; i < nbObjPerLane; ++i) {
            float initialX = xPositions[i];

            // Check for collisions with existing cars
            for (const auto& existingObj : movingObjects) {
                if (initialX < existingObj.x + objWidth + objSpacing &&
                    initialX + objWidth + objSpacing > existingObj.x) {
                    // Adjust the initialX to ensure at least 30.0 spacing
                    initialX = existingObj.x + objWidth + objSpacing;
                }
            }
            initialX -= width / 2; // Center on screen
            movingObjects.emplace_back(createMovingObj(initialX, y + (50.0 * l), laneSpeed * std::pow(-1, l)));
        }
    }
}

void Path::update(float deltaTime) {
    for (auto& obj : movingObjects) {
        obj.update(deltaTime * 0.001);  // Adjust the deltaTime as needed
    }
}

// Default behaviour
bool Path::getsKilled(Character* player) {
    return false;
}