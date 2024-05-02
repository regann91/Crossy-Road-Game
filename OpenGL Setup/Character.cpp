#include "Character.h"

// Constructor implementation
Character::Character(float startX, float startY)
    : GameObject(startX, startY, 50, 50, "../OpenGL\ Setup/textures/character.bmp"), speed(1) 
{}

void Character::move(float dx, float dy) {
    // Move the object
    x += dx*speed;
    y += dy*speed;

    // Move the renderable
    renderable->x = x;
    renderable->y = y;
}