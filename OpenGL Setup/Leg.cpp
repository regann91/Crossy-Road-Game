#include "Leg.h"
#include "TextureManager.h"

Leg::Leg(float startX, float startY, bool isLeftLeg) : BodyPart(startX, startY) {
    if (isLeftLeg) {
        tex = TextureManager::instance()->getTexture("../OpenGL\ Setup/textures/leftLegChar.bmp");
        movementOrient = -1;
    }
    else {
        tex = TextureManager::instance()->getTexture("../OpenGL\ Setup/textures/rightLegChar.bmp");
        movementOrient = 1;
    }
}

// Default animation
void Leg::update(float deltaTime, float newX, float newY, float speed) {
    setPosition(newX, newY);
    localPosY += deltaTime * movementOrient * 0.001 * speed;

    // Check interval
    if (localPosY < -LEG_OFFSET_MAX) {
        // Resets
        localPosY = -LEG_OFFSET_MAX;
        movementOrient *= -1;
    }
    else if (localPosY > LEG_OFFSET_MAX) {
        // Resets
        localPosY = LEG_OFFSET_MAX;
        movementOrient *= -1;
    }
}