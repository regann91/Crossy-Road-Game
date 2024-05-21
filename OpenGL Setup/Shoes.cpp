#include "Shoes.h"

Shoes::Shoes(float startX, float startZ, float time) 
	: Collectible(startX, startZ, MAX_TIME, glm::vec3(1, 0.5, 0.1)) {}

/*
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
*/

void Shoes::tryCollect(std::shared_ptr<Character> player) {
	// Checks activation
	if (!collected && this->collidesWith(player)) {
		// Activates and reset time
		collected = true;
		time = MAX_TIME/2;
		std::cout << "Shoes collected!" << std::endl;
	}
}