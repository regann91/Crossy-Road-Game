#include "Car.h"
#include "Wheel.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#define DEG2RAD 3.14159/180.0


Wheel::Wheel(float startX, float startY, float wheelWidth, float wheelHeight, float radius, float angle, float speed)
    : GameObject(startX, startY, wheelWidth, wheelHeight), radius(radius), angle(angle), speed(speed) {}

void Wheel::rotate(float deltaTime) {
    angle += speed * deltaTime;
}

void Wheel::draw(float x, float y) const {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);
    // Draw the wheel as a circle
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float degInRad = i * DEG2RAD;
        glVertex2f(cos(degInRad) * radius, sin(degInRad) * radius);
    }
    glEnd();
    glPopMatrix();
};

