#include "Road.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <algorithm>  // Include the algorithm header for std::shuffle
#include <random>     // Include the random header for std::default_random_engine


// Constructor implementation
Road::Road(float roadY) : GameObject(0.0, roadY, 800.0, 100.0) {}

float Road::getX() const {
    return x;
}
float Road::getY() const {
    return y;
}

void Road::initCars() {
    const int numCarsPerLane = 4;  // Adjust the number of cars as needed
    const float initialXRange = 800.0;  // Adjust the range of initial x positions
    const float spacing = 30.0;

    std::vector<float> xPositions;
    std::vector<Car> carsLane1;
    std::vector<Car> carsLane2;

    // Generate initial x positions with a larger range
    for (int i = 0; i < numCarsPerLane; ++i) {
        xPositions.push_back(i * spacing + (rand() % static_cast<int>(initialXRange)));
    }

    // Shuffle the x positions randomly
    std::shuffle(xPositions.begin(), xPositions.end(), std::default_random_engine(std::random_device{}()));

    // Generate a single speed for the first lane
    float speedForLane1 = 7.0;

    // Add cars to the road using randomized x positions and the same speed for the lane
    for (int i = 0; i < numCarsPerLane; ++i) {
        float initialX = xPositions[i];
        float carWidth = 50.0;
        float carSpacing = 80.0;  // Ensure at least 80.0 spacing between cars

        bool collision;
        do {
            collision = false;
            // Check for collisions with existing cars
            for (const auto& existingCar : carsLane1) {
                if (initialX < existingCar.x + carWidth + carSpacing &&
                    initialX + carWidth + carSpacing > existingCar.x) {
                    // Adjust the initialX to ensure at least 80.0 spacing
                    initialX = existingCar.x + carWidth + carSpacing;
                    collision = true;
                    break;
                }
            }
        } while (collision);

        carsLane1.emplace_back(initialX, (y + 50.0), 50.0, 50.0, speedForLane1);

        // Sort the cars by their x position
        std::sort(carsLane1.begin(), carsLane1.end(), [](const Car& a, const Car& b) {
            return a.x < b.x;
        });
    }

    // Repeat the process for the second lane
    xPositions.clear();  // Clear the vector for the next set of x positions

    // Generate initial x positions for the second lane
    for (int i = 0; i < numCarsPerLane; ++i) {
        xPositions.push_back(i * spacing + (rand() % static_cast<int>(initialXRange)));
    }

    std::shuffle(xPositions.begin(), xPositions.end(), std::default_random_engine(std::random_device{}()));

    // Generate a single speed for the second lane
    float speedForLane2 = 13.0;

    // Add cars to the road using randomized x positions and the same speed for the lane
    for (int i = 0; i < numCarsPerLane; ++i) {
        float initialX = xPositions[i];
        float carWidth = 50.0;
        float carSpacing = 80.0;  // Ensure at least 80.0 spacing between cars

        bool collision;
        do {
            collision = false;
            // Check for collisions with existing cars
            for (const auto& existingCar : carsLane2) {
                if (initialX < existingCar.x + carWidth + carSpacing &&
                    initialX + carWidth + carSpacing > existingCar.x) {
                    // Adjust the initialX to ensure at least 80.0 spacing
                    initialX = existingCar.x - carWidth - carSpacing;
                    collision = true;
                    break;
                }
            }
        } while (collision);

        carsLane2.emplace_back(initialX, y, 50.0, 50.0, -speedForLane2);

        // Sort the cars by their x position
        std::sort(carsLane2.begin(), carsLane2.end(), [](const Car& a, const Car& b) {
            return a.x < b.x;
        });
    }

    // Combine the cars from both lanes into the main cars vector
    cars.insert(cars.end(), carsLane1.begin(), carsLane1.end());
    cars.insert(cars.end(), carsLane2.begin(), carsLane2.end());
}

void Road::update() {
    for (auto& car : cars) {
        car.update(0.01);  // Adjust the deltaTime as needed
    }
}

// draw implementation
    void Road::draw() const {
        // Custom drawing for the road (gray rectangle)
        glColor3f(0.5, 0.5, 0.5);  // Set color to gray
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        // Draw the dotted line down the middle
        glColor3f(1.0, 1.0, 1.0);  // Set color to white for the line
        glEnable(GL_LINE_STIPPLE);  // Enable line stipple
        glLineStipple(1, 0x00FF); // Set the stipple pattern (alternating 1s and 0s)
        glBegin(GL_LINES);

        // Draw the dotted line in the middle of the road
        float middleY = y + height / 2.0;
        glVertex2f(x, middleY);
        glVertex2f(x + width, middleY);

        glEnd();
        glDisable(GL_LINE_STIPPLE);  // Disable line stipple

        for (const auto& car : cars) {
            car.draw();
        }

    }