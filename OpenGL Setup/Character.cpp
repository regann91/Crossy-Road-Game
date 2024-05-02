#include "Character.h"

// Constructor implementation
Character::Character(float startX, float startY)
    : GameObject(startX, startY, 50, 50, glm::vec4(0.1, 0.8, 1, 1)), speed(1)
{}

void Character::move(float dx, float dy) {
    // Move the object
    x += dx*speed;
    y += dy*speed;

    // Move the renderable
}