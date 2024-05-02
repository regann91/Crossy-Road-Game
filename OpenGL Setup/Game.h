#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <memory>

#include "TextureManager.h"
#include "TextDisplayer.h"
#include "GameObject.h"
#include "Character.h"
#include "Tree.h"
#include "Path.h"
#include "Road.h"
#include "River.h"
#include "Collectible.h"
#include "Shoes.h"
#include "Coin.h"


const float VIEW_WIDTH = 800.0;
const float VIEW_HEIGHT = 600.0;
const float DELTA_TIME = 0.01;
const float MAX_COLLECTIBLES = 3;

class Game {
public:
    Game();         // Constructor
    void init();
    void updateCamera();
    void update();
    void movePlayer(float deltaX, float deltaY);
    void handleInput(char input);
    std::shared_ptr<Character> player() const { return playerChar; }

    // GAME OBJECT AND INFO - used for rendering
    int score;                              // Current score, computed by current best height
    unsigned int coins;                     // Current amount of money
    std::shared_ptr<Shoes> activeShoes;     // Current powerup shoes state

    // Game items
    std::shared_ptr<Character> playerChar;                      // Player character
    std::vector<std::shared_ptr<Tree>> trees;                   // Trees (obstacles)
    std::vector<std::shared_ptr<Path>> paths;                   // Paths (to cross)
    std::vector<std::shared_ptr<Collectible>> collectibles;     // Coins and shoes
    std::shared_ptr<GameObject> flagEnd;                        // Makes game end on Collision

private:
    void spawnCollectibles();       // Spawns collectibles randomly
    bool cheatMode;                 // Activates cheat mode where player passes through obstacles
};