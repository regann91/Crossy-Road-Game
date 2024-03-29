#include "CoverPlate.h"

CoverPlate::CoverPlate(float startX, float startY, float objWidth, float objHeight, std::string texpath, bool orient)
    : GameObject(startX, startY, objWidth, objHeight, texpath), orient(orient) {}

void CoverPlate::draw() const {
    glColor4ub(255, 255, 255, 255);  // Set color to white

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glPushMatrix();  // Save the current transformation matrix

    // Translate the object to the rotation point, rotate it, and then translate it back
    if (orient) {
        glTranslatef(x - width / 2, y, 0);  // Rotate around the leftmost point
    }
    else {
        glTranslatef(x + width / 2, y, 0);  // Rotate around the rightmost point
    }
    glRotatef(rotation, 0, 0, 1);
    if (orient) {
        glTranslatef(-x + width / 2, -y, 0);
    }
    else {
        glTranslatef(-x - width / 2, -y, 0);
    }

    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0);
    glVertex2f(x - width / 2, y - height / 2);
    glTexCoord2d(1.0, 0.0);
    glVertex2f(x + width / 2, y - height / 2);
    glTexCoord2d(1.0, 1.0);
    glVertex2f(x + width / 2, y + height / 2);
    glTexCoord2d(0.0, 1.0);
    glVertex2f(x - width / 2, y + height / 2);
    glEnd();

    glPopMatrix();  // Restore the transformation matrix

    glDisable(GL_TEXTURE_2D);
}