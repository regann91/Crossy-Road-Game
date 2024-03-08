#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

#pragma once
#include "GameObject.h"
#include "Car.h"

class Road : public GameObject {
public:

    std::vector<Car> cars;  // Cars on the road

    // Constructor
    Road(float roadY);

    float getX() const;
    float getY() const;

    void initCars();

    // Override the draw function
    void draw() const override;

    void update();

};

