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
    ~Game();     // Destructor
    Game();    // Constructor
    void init();
    void drawScene();
    void updateCamera();
    void update();
    void movePlayer(float deltaX, float deltaY);
    void handleInput(char input);
    Character* player() const { return playerChar; }

private:
    // Spawns collectibles randomly
    void spawnCollectibles();
    // Activates cheat mode where player passes through obstacles
    bool cheatMode;
    // Stores BG tex
    GLuint backgroundTex;
    // Current score, computed by current best height
    int score;
    // Current amount of money
    unsigned int coins;
    // Current powerup shoes state
    std::shared_ptr<Shoes> activeShoes;

    // Game items
    Character* playerChar;  // Player character
    std::vector<Tree> trees;   // Trees (obstacles)
    std::vector<std::shared_ptr<Path>> paths;   // Paths (to cross)
    std::vector<std::shared_ptr<Collectible>> collectibles;   // Coins and shoes
    GameObject* flagEnd;   // Makes game end on Collision
};