#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>


#include "Character.h"
#include <GL/glut.h>

// Constructor implementation
Character::Character(float startX, float startY, float charWidth, float charHeight)
    : GameObject(startX, startY, charWidth, charHeight) {}

float Character::getX() const {
    return x;
}
float Character::getY() const {
    return y;
}
float Character::getWidth() const {
    return width;
}
float Character::getHeight() const {
    return height;
}




// draw implementation
void Character::draw() const {
    // Custom drawing for the character (blue rectangle)
    glColor3f(0.5, 0.5, 0.0);  
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// collidesWith implementation
bool Character::collidesWith(const GameObject& other) const {
    return (x < other.x + other.width &&
        x + width > other.x &&
        y < other.y + other.height &&
        y + height > other.y);
}

// move implementation
void Character::move(float deltaX, float deltaY) {
    x += deltaX;
    y += deltaY;
}
