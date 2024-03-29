#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <memory>

#include "Character.h"
#include "Tree.h"
#include "Path.h"
#include "Shoes.h"

const float VIEW_WIDTH = 800.0;
const float VIEW_HEIGHT = 600.0;
const float DELTA_TIME = 0.01;
const float MAX_COLLECTIBLES = 3;

class Game {
public:
    // Destructor
    ~Game();

    // Constructor
    Game();

    // Initializes all instances
    void init();

    // Draw all objects
    void drawScene();

    // Update camera position
    void updateCamera();

    // Update game state
    void update();

    // Move player
    void movePlayer(float deltaX, float deltaY);

    // Getters
    Character* player() const { return playerChar; }

private:
    void spawnCollectibles();

    // Background texture
    GLuint backgroundTex;
    // Player
    Character* playerChar;
    // Score (computed by current best height)
    int score;
    // Trees
    std::vector<Tree> trees;
    // Paths
    std::vector<std::shared_ptr<Path>> paths;
    // Collectibles : Shoes and Coins
    std::vector<std::shared_ptr<Collectible>> collectibles;
    std::shared_ptr<Shoes> activeShoes;
    unsigned int coins;
};