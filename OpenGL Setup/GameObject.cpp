#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>

// Constructor implementation
GameObject::GameObject(float startX, float startY, float objWidth, float objHeight, std::string texpath)
    : x(startX), y(startY), width(objWidth), height(objHeight), rotation(0.0f)
{
    // Load texture
    tex = TextureManager::instance()->getTexture(texpath);
}

// Draw implementation
void GameObject::draw() const {
    glColor4ub(255, 255, 255, 255);  // Set color to white

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex);

    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2f(x - width/2, y - height/2);
        glTexCoord2d(1.0, 0.0);
        glVertex2f(x + width/2, y - height/2);
        glTexCoord2d(1.0, 1.0);
        glVertex2f(x + width/2, y + height/2);
        glTexCoord2d(0.0, 1.0);
        glVertex2f(x - width / 2, y + height/2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Draw fixed on screen (object to pass is character)
void GameObject::drawFixed(GameObject* object) const {
    glColor4ub(255, 255, 255, 255);  // Set color to white
    float posY = y + object->y;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2f(x - width / 2, posY - height / 2);
        glTexCoord2d(1.0, 0.0);
        glVertex2f(x + width / 2, posY - height / 2);
        glTexCoord2d(1.0, 1.0);
        glVertex2f(x + width / 2, posY + height / 2);
        glTexCoord2d(0.0, 1.0);
        glVertex2f(x - width / 2, posY + height / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


// Collision check between 2 objects
bool GameObject::collidesWith(GameObject other) const
{
    return (x - width/2 < other.x + other.width/2 &&
        x + width/2 > other.x - other.width/2 &&
        y - height/2 < other.y + other.height/2 &&
        y + height/2 > other.y - other.height /2
    );
}

void GameObject::rotate(float speed) {
    rotation += speed;  // Increment the rotation angle

// Keep the rotation angle within [0, 360)
    if (rotation >= 360.0f) {
        rotation -= 360.0f;
    }
    else if (rotation < 0.0f) {
        rotation += 360.0f;
    }
}

void GameObject::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}