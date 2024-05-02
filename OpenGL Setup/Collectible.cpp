#include "Collectible.h"

const float Collectible::SPAWN_RATE = 60;
const float Collectible::MAX_TIME = 300000;

Collectible::Collectible(float startX, float startY, float time, glm::vec4 color)
	: GameObject(startX, startY, 35, 35, color), time(time), collected(false) {}

void Collectible::update(float deltaTime, Character* player) {
	// Update time and checks activation
	time -= deltaTime;
	tryCollect(player);
}

// Default behaviour
void Collectible::tryCollect(Character* player) {
	if (player->collidesWith(*this)) {
		// Activates
		collected = true;
	}
}