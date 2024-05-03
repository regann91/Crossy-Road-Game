#include "Character.h"

// Constructor implementation
Character::Character(float startX, float startZ)
    : GameObject(startX, 0, startZ, 50, 70, 50, glm::vec4(0.1, 0.8, 1, 1)), speed(1)
{}

void Character::move(float dx, float dy, float dz) {
    // Move the object
    x += dx*speed;
    y += dy*speed;
    z += dy*speed;

    // Move the renderable
    renderable->translate(dx * speed, dy * speed, dz * speed);
}