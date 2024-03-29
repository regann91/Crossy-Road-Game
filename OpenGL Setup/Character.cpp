#include "Character.h"

// Constructor implementation
Character::Character(float startX, float startY)
    : GameObject(startX, startY, 24, 50, "../OpenGL\ Setup/textures/character.bmp"), speed(1) {}

// move implementation
void Character::move(float deltaX, float deltaY) {
    x += speed * deltaX;
    y += speed * deltaY;
}