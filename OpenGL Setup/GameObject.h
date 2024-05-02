#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <string>
#include <iostream>
#include "Renderable.h"

class GameObject {
public:
    float x, y;  // Position
    float width, height;  // Dimensions
    std::shared_ptr<Renderable> renderable;
    
    // Constructor
    GameObject(float startX, float startY, float objWidth, float objHeight, std::string texpath);

    // Constructor
    GameObject() {}

    // Moving functions
    void move(float dx, float dy);
    void setPosition(float newX, float newY);

    // Calls draw from renderable
    void draw();
    void drawFixed(std::shared_ptr<Renderable> r);

    // Collision check between 2 objects
    bool collidesWith(GameObject obj) const;
};