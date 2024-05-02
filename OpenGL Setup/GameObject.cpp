#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Constructor implementation
GameObject::GameObject(float startX, float startY, float objWidth, float objHeight, glm::vec4 color)
    : x(startX), y(startY), width(objWidth), height(objHeight)
{
    renderable = std::make_shared<Renderable>(color);
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
}

void GameObject::setPosition(float newX, float newY) {
    // Move the object
    x = newX;
    y = newY;

    // Move the renderable
}