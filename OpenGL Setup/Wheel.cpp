#include "Wheel.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

Wheel::Wheel(float x, float y, float width, float height, std::string texPath)
    : GameObject(x, y, width, height, "../OpenGL\ Setup/textures/wheel.bmp"), rotation(0.0f) {}

void Wheel::draw() const {
    glColor4ub(255, 255, 255, 255);  // Set color to white
    glPushMatrix();  // Save the current transformation matrix
        // Translate to the object's position
    glTranslatef(x, y, 0);

    // Apply the rotation
    glRotatef(rotation, 0, 0, 1);

    // Translate back to the original position
    glTranslatef(-x, -y, 0);

    GameObject::draw();  // Draw the wheel

    glPopMatrix();  // Restore the previous transformation matrix
}

void Wheel::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void Wheel::rotate(float speed) {
    rotation -= speed * 0.01f;  // Increment the rotation angle

    // Keep the rotation angle within [0, 360)
    if (rotation >= 360.0f) {
        rotation -= 360.0f;
    }
    else if (rotation < 0.0f) {
        rotation += 360.0f;
    }
}