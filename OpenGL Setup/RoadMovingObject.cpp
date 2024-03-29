#include "RoadMovingObject.h"
#include "Wheel.h"
#include <chrono>


RoadMovingObject::RoadMovingObject(float startX, float startY, float movingWidth, float movingHeight, std::string texPath, float movingSpeed, float laneW, bool isTruck)
    : GameObject(startX, startY - movingHeight/2, movingWidth, movingHeight, texPath), speed(movingSpeed), laneWidth(laneW), isTruck(isTruck), 
    leftWheel(startX - movingWidth / 2 + 12, startY - movingHeight / 2 + 8, 18, 18, "../OpenGL\ Setup/textures/wheel.bmp"),
    rightWheel(startX + movingWidth / 2 - 12, startY - movingHeight / 2 + 8, 18, 18, "../OpenGL\ Setup/textures/wheel.bmp"),
    coverPlate(startX + 10, startY, 30, 30, "../OpenGL\ Setup/textures/coverplate.bmp", 0)
{}


// Draw implementation
void RoadMovingObject::draw() const {
    glColor4ub(255, 255, 255, 255);  // Set color to white

    // Orientation depending on speed : is either 0 or 1
    bool orient = speed < 0;


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_QUADS);
        glTexCoord2d(orient, 0.0);
        glVertex2f(x - width / 2, y - height/2);
        glTexCoord2d(!orient, 0.0);
        glVertex2f(x + width / 2, y - height/2);
        glTexCoord2d(!orient, 1.0);
        glVertex2f(x + width / 2, y + height/2);
        glTexCoord2d(orient, 1.0);
        glVertex2f(x - width / 2, y + height/2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    leftWheel.draw();
    rightWheel.draw();

    if (isTruck) {
        coverPlate.draw();
    }

}

// Update function implementation
void RoadMovingObject::update(float deltaTime) {
    // Update the car position based on speed and elapsed time
    x += speed * deltaTime;

    // Check if the car is out of the window, reset its position to the opposite side
    if (x > laneWidth/2) {
        x = -laneWidth/2;  // Move to the left side
    }
    else if (x < -laneWidth/2) {
        x = laneWidth/2;  // Move to the right side
    }
    // Update the wheel positions
    leftWheel.setPosition(x - width / 2 + 12, y - height / 2 + 8);
    rightWheel.setPosition(x + width / 2 - 12, y - height / 2 + 8);

    // Rotate the wheels
    float wheelRotationSpeed = speed * deltaTime * 360;  // Adjust this value as needed
    leftWheel.rotate(wheelRotationSpeed);
    rightWheel.rotate(wheelRotationSpeed);

    // Update the cover plate position and rotation
    if (isTruck) {
        coverPlate.orient = speed < 0;
        if (coverPlate.orient) {
            coverPlate.setPosition(x + 10, y);
            coverPlate.rotateWithinRange(speed, deltaTime, 0.0f, 45.0f);
        }
        else {
            coverPlate.setPosition(x - 10, y);
            coverPlate.rotateWithinRange(-speed, deltaTime, -45.0f, 0.0f);
        }
    }
}