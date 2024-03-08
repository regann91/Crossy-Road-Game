#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

#pragma once
#include "GameObject.h"

class Character : public GameObject {
public:
    // Constructor
    Character(float startX, float startY, float charWidth, float charHeight);
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    // Override the draw function
    void draw() const override;

    // Check collision with another game object
    bool collidesWith(const GameObject& other) const;

    // Move the character based on keyboard input
    void move(float deltaX, float deltaY);
};
