#include "Character.h"
#include <glm/gtx/matrix_decompose.hpp>
#include "Renderer.h"

// Constructor implementation
Character::Character(float startX, float startZ)
    : GameObject(startX, 35, startZ, 50, 70, 50, glm::vec3(0.43, 0.46, 0.77), 0, "charTex.bmp"), speed(1)
{}

void Character::move(float dx, float dy, float dz) {
    // Move the object
    x += dx;
    y += dy;
    z += dz;

    // Move the renderable
    renderable->translate(dx / width, dy / height, dz / depth);
    // Move the point light
    Renderer::instance()->pointLight.position.x += dx;
    Renderer::instance()->pointLight.position.z += dz;
}

void Character::setPosition(float newX, float newY, float newZ) {
    // Move the point light
    Renderer::instance()->pointLight.position.x += newX - x;
    Renderer::instance()->pointLight.position.y += newY - y;
    Renderer::instance()->pointLight.position.z += newZ - z;

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