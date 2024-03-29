#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <string>
#include <iostream>

class GameObject {
public:
    float x, y;  // Position
    float width, height;  // Dimensions
    float rotation;
    GLuint tex;   // Texture

    // Constructor
    GameObject(float startX, float startY, float objWidth, float objHeight, std::string texpath);

    // Constructor
    GameObject() {}

    // Function for drawing the object
    virtual void draw() const;

    // Function for drawing the object in a fixed place on screen (relative to character position)
    void drawFixed(GameObject* object) const;

    // Collision check between 2 objects
    bool collidesWith(GameObject obj) const;

    virtual void rotate(float speed);

    void setPosition(float newX, float newY);

};