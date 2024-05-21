#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>
#include <memory>
#include "NormalMappedRenderable.h"

// Constructor implementation
GameObject::GameObject(float startX, float startY, float startZ, float objWidth, float objHeight, float objDepth, glm::vec3 color, float rotation, std::string tex)
    : x(startX), y(startY), z(startZ), width(objWidth), height(objHeight), depth(objDepth), rotation(rotation)
{
    renderable = std::make_shared<Renderable>("cube.obj", color, tex);
    renderable->setTransform(
        Renderable::getTrans(x, y, z) *
        Renderable::getRot(rotation, glm::vec3(0, 0, 1)) * 
        Renderable::getScale(width, height, depth)
    );
}

// Collision check between 2 objects (only check x and z)
bool GameObject::collidesWith(std::shared_ptr<GameObject> other) const
{
    //std::cout << this->x << " " << other->x << " et " << this->z << " " << other->z << std::endl;
    
    return (x - width/2 < other->x + other->width/2 &&
        x + width/2 > other->x - other->width/2 &&
        z - depth / 2 < other->z + other->depth / 2 &&
        z + depth / 2 > other->z - other->depth / 2
    );
}

// Moving function
void GameObject::move(float dx, float dy, float dz) {
    // Move the object
    x += dx;
    y += dy;
    z += dz;

    // Move the renderable
    renderable->translate(dx/width, dy/height, dz/depth);
}

void GameObject::setPosition(float newX, float newY, float newZ) {
    // Move the object
    x = newX;
    y = newY;
    z = newZ;

    // Move the renderable to where it should go
    renderable->setTransform(
        Renderable::getTrans(x, y, z) *
        Renderable::getRot(rotation, glm::vec3(0, 0, 1)) * 
        Renderable::getScale(width, height, depth)
    );
}

void GameObject::draw() const
{ 
    // Check of class
    NormalMappedRenderable* ptr = dynamic_cast<NormalMappedRenderable*>(renderable.get());
    if (ptr != nullptr) {
        // Draws Normal mapped renderable
        ptr->draw();
    }
    else {
        renderable->draw(); // Draws classic renderable
    }
}