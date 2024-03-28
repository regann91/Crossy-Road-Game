#include "Wheel.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

Wheel::Wheel(float x, float y, float width, float height)
    : GameObject(x, y, width, height, "../OpenGL\ Setup/textures/wheel.bmp"), rotation(0.0f) {}

void Wheel::draw() const {
    glColor4ub(255, 255, 255, 255);  // Set color to white
    glPushMatrix();  // Save the current transformation matrix
    // Translate to the center of the wheel, rotate, then translate back
    glTranslatef(x, y, 0.0f);
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);
    glTranslatef(-x, -y, 0.0f);

    GameObject::draw();  // Draw the wheel

    glPopMatrix();  // Restore the previous transformation matrix
}

void Wheel::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void Wheel::rotate(float speed) {
    // Adjust the rotation based on the speed
    rotation -= speed * 0.0001f;
}