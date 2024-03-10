#include "Tree.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

Tree::Tree(float x, float y, float width, float height)
    : GameObject(x, y, width, height, glm::vec3(237,137,196)) {}

float Tree::getX() const {
    return x;
}
float Tree::getY() const {
    return y;
}