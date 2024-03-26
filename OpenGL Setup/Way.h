#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

#include "GameObject.h"
#include "MovingObject.h"
#include "Character.h"

#define WAY 0
#define ROAD 1
#define RIVER 2

#define DELTA_TIME 0.1


class Way : public GameObject {
public:
    std::vector<MovingObject> movingObjects;  // Boulders/Trunks on the road/river

    // Destructor
    ~Way();

    // Constructor
    Way(float roadY, int type = ROAD);

    // Getters
    float getX() const;
    float getY() const;
    std::vector<MovingObject> getMovingObjects() const { return movingObjects; }

    void initMovingObjects();

    // Override the draw function
    void draw();

    // Override the draw function
    bool collided(Character player);

    void update();

private:
    // River, Road, none
    int type;
};