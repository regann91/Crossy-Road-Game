#include "Tree.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

Tree::Tree(float x, float y, float width, float height)
    : GameObject(x, y, width, height) {}

float Tree::getX() const {
    return x;
}
float Tree::getY() const {
    return y;
}


// draw implementation
void Tree::draw() const {
    // Custom drawing for the tree (green rectangle)
    glColor3f(0.6, 0.3, 0.0);  // Brown color
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}
