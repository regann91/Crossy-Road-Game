#pragma once
#include <memory>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>

class GameObject {
public:
    float x, y;  // Position
    float width, height;  // Dimensions
    glm::vec3 color;   // Color

    // Constructor 1 (color in 0 to 255 RGB format
    GameObject(float startX = 400, float startY = 50, float objWidth = 50, float objHeight = 50, glm::vec3 color = {1,1,1});

    // Virtual function for drawing the object
    void draw() const;
};