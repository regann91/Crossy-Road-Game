#include "Character.h"
#include <glm/gtx/matrix_decompose.hpp>


// Constructor implementation
Character::Character(float startX, float startZ)
    : GameObject(startX, 35, startZ, 50, 70, 50, glm::vec4(0.43, 0.46, 0.77, 1)), speed(1)
{}

void Character::move(float dx, float dy, float dz) {
    // Move the object
    x += dx;
    y += dy;
    z += dz;

    // Move the renderable
    renderable->translate(dx / width, dy / height, dz / depth);
}