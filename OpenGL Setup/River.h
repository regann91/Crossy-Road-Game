#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

#pragma once
#include "GameObject.h"
#include "Character.h"


class River : public GameObject {
public:

    // Constructor
    River(float riverX, float riverY, float riverWidth);
    float getX() const;
    float getY() const;


    // Override the draw function
    void draw() const override;

    void update();

};

