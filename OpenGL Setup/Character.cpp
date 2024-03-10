#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

#include "TextureManager.h"
#include "Character.h"


// Constructor implementation
Character::Character(float startX, float startY, float charWidth, float charHeight)
    : GameObject(startX, startY, charWidth, charHeight) 
{
    color = glm::vec3(176, 63, 130)/256.0f;
}

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

    // Checks where the player wants to move -> collisions
    updateCamera();
}

// Updates the camera according to the Y player position
void Character::updateCamera() {
    int posX = WIDTH / 2 + width / 2;
    int posY = y + height / 2;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(- WIDTH / 2 + posX, WIDTH / 2 + posX, - HEIGHT / 2 + posY, HEIGHT / 2 + posY);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
