#pragma once
#include <vector>
#include "Way.h"
#include "Tree.h"

class Game {
public:
    // Destructor
    ~Game();

    // Constructor
    Game();

    // Get all game objects (except player)
    std::vector<std::shared_ptr<Way>> getWays() const { return ways; }
    std::vector<Tree> getTrees() const { return trees; }

    // Initializes all instances
    void init();

    // Draw all objects
    void drawObjects();

    // Updates all moving objects positions
    void updateWays();

private:
    // Background
    GameObject bg;
    // Non moving objects
    std::vector<Tree> trees;
    // Moving objects on ways
    std::vector<std::shared_ptr<Way>> ways;
};