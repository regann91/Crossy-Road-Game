#include "GameObject.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "TextureManager.h"

// Constructor colored implementation
GameObject::GameObject(float startX, float startY, float objWidth, float objHeight, glm::vec3 color)
    : x(startX), y(startY), width(objWidth), height(objHeight) {
    color = color / 256.0f;
}

// draw implementation
void GameObject::draw() const {
    // Default drawing behavior (a simple rectangle)
    
    glColor3f(color[0], color[1], color[2]);  // Set color to white
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}
