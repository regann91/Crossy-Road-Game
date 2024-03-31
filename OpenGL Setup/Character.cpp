#include "Character.h"

// Constructor implementation
Character::Character(float startX, float startY)
    : GameObject(startX, startY, 50, 50, "../OpenGL\ Setup/textures/bodyChar.bmp"), speed(1) 
{
    backpack = GameObject(startX, startY, 50, 50, "../OpenGL\ Setup/textures/backpackChar.bmp");
    head = BodyPart(startX, startY, "../OpenGL\ Setup/textures/headChar.bmp");
    legR = Leg(startX, startY, false);
    legL = Leg(startX, startY, true);
    armR = Arm(startX, startY, false);
    armL = Arm(startX, startY, true);
}

// move implementation
void Character::move(float deltaX, float deltaY) {
    x += speed * deltaX;
    y += speed * deltaY;
}


void Character::update(float deltaTime) {
    legL.update(deltaTime, x, y, speed);
    legR.update(deltaTime, x, y, speed);
    armL.update(deltaTime, x, y, speed);
    armR.update(deltaTime, x, y, speed);
    head.update(deltaTime, x, y, speed);
    backpack.setPosition(x, y);
}


// Draw implementation
void Character::draw() const {
    backpack.draw();
    head.draw();
    legL.draw();
    legR.draw();
    armL.draw();
    armR.draw();
    GameObject::draw();
}