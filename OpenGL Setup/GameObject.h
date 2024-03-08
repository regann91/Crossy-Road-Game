#pragma once

class GameObject {
public:
    float x, y;  // Position
    float width, height;  // Dimensions

    // Constructor
    GameObject(float startX, float startY, float objWidth, float objHeight);

    // Virtual function for drawing the object
    virtual void draw() const;
};
