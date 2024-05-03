#include "Collectible.h"

const float Collectible::SPAWN_RATE = 60;
const float Collectible::MAX_TIME = 300000;

Collectible::Collectible(float startX, float startZ, float time, glm::vec4 color)
	: GameObject(startX, 30, startZ, 30, 30, 15, color), time(time), collected(false) {}

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