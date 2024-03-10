#include "Way.h"
#include <iostream>

#include <algorithm>  // Include the algorithm header for std::shuffle
#include <random>     // Include the random header for std::default_random_engine


// Destructor
Way::~Way() {
    for (const auto& obj : movingObjects) {
        delete &obj;
    }
}

// Constructor implementation
Way::Way(float roadY, int type) : type(type) {
    x = 0;
    y = roadY;
    width = WIDTH;
    height = 100;
    if (type == ROAD) {
        color = glm::vec3(50,50,110)/255.0f;
        return;
    }
    if (type == RIVER) {
        color = glm::vec3(116,223,237)/255.0f;
        return;
    }
}

float Way::getX() const {
    return x;
}
float Way::getY() const {
    return y;
}

void Way::initMovingObjects() {

    // Number of objects per lane
    int numObj;
    // Colors
    glm::vec3 colors;


    switch (type) {
        case RIVER:
            numObj = 3;
            colors = glm::vec3(84,100,102);
        default:
            numObj = 5;
            colors = glm::vec3(165,134,148);
    }

    const float initialXRange = 800.0;  // Adjust the range of initial x positions
    const float spacing = initialXRange / numObj;
    const float objWidth = type == RIVER ? 120 : 50;
    const float objSpacing = 30;  // Ensure at least 30.0 spacing between cars

    std::vector<float> xPositions;
    // LANE GENERATION LOOP : 2 lanes
    for (int l = 0; l < 2; l++) {
        std::cout << l << std::endl;
        // Repeat the process for the second lane
        xPositions.clear();  // Clear the vector for the next set of x positions

        // Generate initial x positions with a larger range
        for (int i = 0; i < numObj; ++i) {
            xPositions.push_back(i * spacing + (rand() % static_cast<int>(initialXRange)));
        }

        // Shuffle the x positions randomly
        std::shuffle(xPositions.begin(), xPositions.end(), std::default_random_engine(std::random_device{}()));

        // Generate a single speed for the first lane
        float speedForLane1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 4.0;

        // Add cars to the road using randomized x positions and the same speed for the lane
        for (int i = 0; i < numObj; ++i) {
            float initialX = xPositions[i];

            // Check for collisions with existing cars
            for (const auto& existingObj : movingObjects) {
                if (initialX < existingObj.x + objWidth + objSpacing &&
                    initialX + objWidth + objSpacing > existingObj.x) {
                    // Adjust the initialX to ensure at least 30.0 spacing
                    initialX = existingObj.x + objWidth + objSpacing;
                }
            }
            movingObjects.emplace_back(MovingObject(initialX, y + (50.0 * l), objWidth, 50.0, colors, (-1*l) * speedForLane1));
        }
    }
}

void Way::update() {
    for (auto& obj : movingObjects) {
        obj.update(DELTA_TIME * 0.001);  // Adjust the deltaTime as needed
    }
}

// draw implementation
void Way::draw() {
    // Drawing of path 
    GameObject::draw();

    for (const auto& obj : movingObjects) {
        obj.draw();
    }

}

bool Way::collided(Character player) {
    if (player.collidesWith(*this)) {
        // River behaviour
        if (type == RIVER) {
            // If they are in the river, then check collisions for moving objects
            for (MovingObject obj : movingObjects) {
                if (player.collidesWith(obj)) {
                    // Move the player with the object
                    player.move(10, 0);
                    return false;
                }
            }
            // A player has fallen in a river in Crossy Roads !
            return true;
        }
        // Road behaviour
        if (type == ROAD) {
            // If they are in the road, then check collisions for moving objects
            for (MovingObject obj : movingObjects) {
                if (player.collidesWith(obj)) return true;
            }
        }
    }
    return false;
}


// -------------
