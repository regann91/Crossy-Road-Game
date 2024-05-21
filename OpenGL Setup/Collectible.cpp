#include "Collectible.h"

const float Collectible::SPAWN_RATE = 70;
const float Collectible::MAX_TIME = 30000;

Collectible::Collectible(float startX, float startZ, float time, glm::vec3 color)
	: GameObject(startX, 30, startZ, 30, 30, 15, color), time(time), collected(false) {}

void Collectible::update(float deltaTime, std::shared_ptr<Character> player) {
	// Update time and checks activation
	time -= deltaTime;
	tryCollect(player);
}

// Default behaviour
void Collectible::tryCollect(std::shared_ptr<Character> player) {
	if (this->collidesWith(player)) {
		// Activates
		collected = true;
	}
}