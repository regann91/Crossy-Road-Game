#include "Shoes.h"

Shoes::Shoes(float startX, float startY, float time) 
	: Collectible(startX, startY, MAX_TIME, glm::vec4(1, 0.5, 0.1, 1)) {}

// This draws a bar relative to player Y position
void Shoes::drawBar(Character* player) const {
	glColor4ub(207, 100, 80, 255);  // Set color to orange

	float posX = 220;
	float posY = -280 + player->y;
	float offset = 2 * time / MAX_TIME * 150;

	glBegin(GL_QUADS);
		// First quad (orange BG)
		glVertex2f(posX, posY);
		glVertex2f(posX + 150, posY);
		glVertex2f(posX + 150, posY + 20);
		glVertex2f(posX, posY + 20);
	glEnd();

	// Second quad - grey bar 
	glColor4ub(80, 80, 80, 255);
	glBegin(GL_QUADS);
		glVertex2f(posX + offset, posY);
		glVertex2f(posX + 150, posY);
		glVertex2f(posX + 150, posY + 20);
		glVertex2f(posX + offset, posY + 20);
	glEnd();
}

void Shoes::tryCollect(Character* player) {
	// Checks activation
	if (!collected && player->collidesWith(*this)) {
		// Activates and reset time
		collected = true;
		time = MAX_TIME/2;
	}
}