#include "Coin.h"

Coin::Coin(float startX, float startY, float time) 
	: Collectible(startX, startY, MAX_TIME, glm::vec4(1, 0.8, 0.1, 1)) {}