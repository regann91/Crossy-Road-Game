#include "Car.h"
#include "Wheel.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

// Constructor implementation
Car::Car(float startX, float startY, float carWidth, float carHeight, float carSpeed)
    : GameObject(startX, startY, carWidth, carHeight), speed(carSpeed),
    leftWheel(startX+5, startY-5, 0.3 * carWidth, 0.3 * carHeight, 0.2 * carHeight, 0.0, carSpeed), 
    rightWheel(startX + 5, startY - 5, 0.3 * carWidth, 0.3 * carHeight, 0.2 * carHeight, 0.0, carSpeed) {}

//Wheel(float startX, float startY, float wheelWidth, float wheelHeight, float radius, float angle, float speed);


// Update function implementation
void Car::update(float deltaTime) {
    // Update the car position based on speed and elapsed time
    x += speed * deltaTime;

    // Update the wheels
    leftWheel.rotate(deltaTime);
    rightWheel.rotate(deltaTime);

    // Check if the car is out of the window, reset its position to the opposite side
    if (x > 800) {
        x = -width;  // Move to the left side
    }
    else if (x < -width) {
        x = 800;  // Move to the right side
    }
}

// draw implementation
void Car::draw() const {
    // Custom drawing for the car (e.g., a rectangle)
    glColor3f(1.0, 0.0, 0.0);  // Set color to red for the car
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Draw the wheels
    leftWheel.draw(x, y);
    rightWheel.draw(x + width, y);
}
