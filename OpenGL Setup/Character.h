#pragma once
#include <iostream>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <vector>

#include "Tree.h"
#include "GameObject.h"

// Window height and width
#define WIDTH 800
#define HEIGHT 600
// Length of one player step
#define MOVESTEP 50.0

class Character : public GameObject {
public:
    // Constructor
    Character(float startX = WIDTH/2, float startY = 0, float charWidth = 24, float charHeight = 50);
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    // Check collision with another game object
    bool collidesWith(const GameObject& other) const;

    // Move the character based on keyboard input
    void move(float deltaX, float deltaY);

    // Updates the camera according to the player position
    void updateCamera();

};