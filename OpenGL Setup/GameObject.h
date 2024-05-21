#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec4.hpp>
#include <string>
#include <iostream>
#include "Renderable.h"

class GameObject {
public:
    float x, y, z;  // Position
    float width, height, depth;  // Dimensions
    float rotation;
    std::shared_ptr<Renderable> renderable;
    
    // Constructor
    GameObject(float startX, float startY, float startZ, float objWidth, float objHeight, float objDepth, glm::vec3 color, float rotation = 0, std::string tex = "defaultTex.bmp");

    // Constructor
    GameObject() {}

    // Collision check between 2 objects
    bool collidesWith(std::shared_ptr<GameObject> obj) const;

    // Draw from renderable
    void draw() const;

    // Moving functions
    void move(float dx, float dy, float dz);
    void setPosition(float newX, float newY, float newZ);
};