#include "GameObject.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Constructor implementation
GameObject::GameObject(float startX, float startY, float objWidth, float objHeight)
    : x(startX), y(startY), width(objWidth), height(objHeight) {}

// draw implementation
void GameObject::draw() const {
    // Default drawing behavior (a simple rectangle)
    glColor3f(0.0, 0.0, 0.0);  // Set color to black
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}
