#include "River.h"
#include "Character.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <algorithm>  // Include the algorithm header for std::shuffle
#include <random>     // Include the random header for std::default_random_engine


// Constructor implementation
River::River(float riverX, float riverY, float riverWidth) : GameObject(riverX, riverY, riverWidth, 100.0) {}

float River::getX() const {
    return x;
}
float River::getY() const {
    return y;
}


// draw implementation
void River::draw() const {
    glColor3f(0.372549, 0.623529, 0.623529);  // Set color to blue
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();


}
