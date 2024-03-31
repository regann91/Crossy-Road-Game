#include "BodyPart.h"

BodyPart::BodyPart(float startX, float startY, std::string texPath)
    : GameObject(startX, startY, 50, 50, texPath), localPosX(0), localPosY(0), localRot(0), movementOrient(1) {}

void BodyPart::draw() const {
    glColor4ub(255, 255, 255, 255);  // Set color to white
    glPushMatrix();  // Save the current transformation matrix
    // Translate to the object's position
    glTranslatef(x, y, 0);

    // Apply the rotation
    glRotatef(rotation + localRot, 0, 0, 1);

    // Translate back to the original position + offset
    glTranslatef(-x + localPosX, -y + localPosY, 0);

    GameObject::draw();  // Draw the wheel

    glPopMatrix();  // Restore the previous transformation matrix
}

// Default animation
void BodyPart::update(float deltaTime, float newX, float newY, float speed) {
    setPosition(newX, newY);
    localPosY += deltaTime * movementOrient * 0.00025 * speed;

    // Check interval
    if (localPosY < -POS_OFFSET_MAX) {
        // Resets
        localPosY = -POS_OFFSET_MAX;
        movementOrient *= -1;
    }
    else if (localPosY > POS_OFFSET_MAX) {
        // Resets
        localPosY = POS_OFFSET_MAX;
        movementOrient *= -1;
    }
}