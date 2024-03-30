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
    void spawnCollectibles();
    bool cheatMode;
    GLuint backgroundTex;
    Character* playerChar;
    int score;      // computed by current best height
    std::vector<Tree> trees;
    std::vector<std::shared_ptr<Path>> paths;
    std::vector<std::shared_ptr<Collectible>> collectibles;
    std::shared_ptr<Shoes> activeShoes;
    unsigned int coins;
};