#include "Arm.h"
#include "TextureManager.h"

Arm::Arm(float startX, float startY, bool isLeftArm) : BodyPart(startX, startY) {
    // Arm offset
    localPosY = 2;
    if (isLeftArm) {
        tex = TextureManager::instance()->getTexture("../OpenGL\ Setup/textures/leftArmChar.bmp");
        localPosX = -7;
    }
    else {
        tex = TextureManager::instance()->getTexture("../OpenGL\ Setup/textures/rightArmChar.bmp");
        localPosX = 7;
    }
}

// Custom animation
void Arm::update(float deltaTime, float newX, float newY, float speed) {
    setPosition(newX, newY);
    localRot += deltaTime * movementOrient * 0.003 * speed;

    // Check interval
    if (localRot < -ROT_OFFSET_MAX) {
        // Resets
        localRot = -ROT_OFFSET_MAX;
        movementOrient *= -1;
    }
    else if (localRot > ROT_OFFSET_MAX) {
        // Resets
        localRot = ROT_OFFSET_MAX;
        movementOrient *= -1;
    }
}