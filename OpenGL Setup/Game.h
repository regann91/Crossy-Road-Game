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
const float DELTA_TIME = 0.03;

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
    void spawnPowerUps();

    // Background texture
    GLuint backgroundTex;
    // Player
    Character* playerChar;
    // Trees
    std::vector<Tree> trees;
    // Paths
    std::vector<std::shared_ptr<Path>> paths;
    // Powerup shoes
    std::vector<Shoes> powerups;
    std::shared_ptr<Shoes> activeShoes;
};