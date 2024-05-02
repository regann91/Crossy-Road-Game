#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>

// Constructor implementation
GameObject::GameObject(float startX, float startY, float objWidth, float objHeight, std::string texpath)
    : x(startX), y(startY), width(objWidth), height(objHeight)
{
    renderable = std::make_shared<Renderable>(startX, startY, objWidth, objHeight, texpath);
}

// Collision check between 2 objects
bool GameObject::collidesWith(GameObject other) const
{
    return (x - width/2 < other.x + other.width/2 &&
        x + width/2 > other.x - other.width/2 &&
        y - height/2 < other.y + other.height/2 &&
        y + height/2 > other.y - other.height /2
    );
}

// Moving function
void GameObject::move(float dx, float dy) {
    // Move the object
    x += dx;
    y += dy;

    // Move the renderable
    renderable->x = x;
    renderable->y = y;
}

void GameObject::setPosition(float newX, float newY) {
    // Move the object
    x = newX;
    y = newY;

    // Move the renderable
    renderable->x = newX;
    renderable->y = newY;
}

void GameObject::draw() {
    renderable->draw();
}

void GameObject::drawFixed(std::shared_ptr<Renderable> r) {
    renderable->drawFixed(r);
}