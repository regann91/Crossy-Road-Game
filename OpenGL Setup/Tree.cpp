#include "Tree.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>

Tree::Tree(float x, float z, float width, float height, float depth)
    : GameObject(x, height/2, z, width, height, depth, glm::vec4(0.13,0.41,0.64, 1)) {}
