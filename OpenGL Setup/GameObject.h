#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec4.hpp>
#include <string>
#include <iostream>
#include "Renderable.h"

class GameObject {
public:
    float x, y;  // Position
    float width, height;  // Dimensions
    std::shared_ptr<Renderable> renderable;
    
    // Constructor
    GameObject(float startX, float startY, float objWidth, float objHeight, glm::vec4 color);

    // Constructor
    GameObject() {}

    // Collision check between 2 objects
    bool collidesWith(GameObject obj) const;

    // Draw from renderable
    void draw() const { renderable->draw(); }

    // Moving functions
    void move(float dx, float dy);
    void setPosition(float newX, float newY);
};