#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>


// Constructor implementation
GameObject::GameObject(float startX, float startY, float startZ, float objWidth, float objHeight, float objDepth, glm::vec4 color)
    : x(startX), y(startY), width(objWidth), height(objHeight)
{
    renderable = std::make_shared<Renderable>(color);
    setPosition(x, y, z);
}

// Collision check between 2 objects
bool GameObject::collidesWith(GameObject other) const
{
    return (x - width/2 < other.x + other.width/2 &&
        x + width/2 > other.x - other.width/2 &&
        y - height/2 < other.y + other.height/2 &&
        y + height/2 > other.y - other.height /2 &&
        z - height / 2 < other.z + other.depth / 2 &&
        z + height / 2 > other.z - other.depth / 2
    );
}

// Moving function
void GameObject::move(float dx, float dy, float dz) {
    // Move the object
    x += dx;
    y += dy;
    z += dz;

    // Move the renderable
    renderable->translate(dx, dy, dz);
}

void GameObject::setPosition(float newX, float newY, float newZ) {
    // Move renderable to origin
    renderable->translate(-x, -y, -z);

    // Move the object
    x = newX;
    y = newY;
    z = newZ;

    // Move the renderable to where it should go
    renderable->translate(newX, newY, newZ);
    
}