
#include "Game.h"
#include "Tree.h"
#include "Character.h"

Game::~Game() {
    for (const auto& way : ways) {
        delete &way;
    }
}

// Constructor
Game::Game() {
    // Example instances of game objects
    ways = {
        std::make_shared<Way>(150, ROAD),
        std::make_shared<Way>(450, RIVER),
        std::make_shared<Way>(700, ROAD)
    };

    trees = {
        // Init trees
        Tree(100.0, 350.0, 50.0, 50.0),
        Tree(100.0, 750.0, 50.0, 50.0),
        Tree(250.0, 300.0, 50.0, 50.0),
        Tree(250.0, 550.0, 50.0, 50.0),
        Tree(350.0, 400.0, 50.0, 50.0),
        Tree(450.0, 250.0, 50.0, 50.0),
        Tree(500.0, 700.0, 50.0, 50.0),
        Tree(550.0, 100.0, 50.0, 50.0),
        Tree(600.0, 350.0, 50.0, 50.0),
        Tree(700.0, 300.0, 50, 50.0)
    };
}

void Game::init()
{
    // Road cars initialization
    for (const auto& way : ways) {
        way -> initMovingObjects();
    }
}

void Game::drawObjects() {
    // Render all trees
    for (const auto& tree : trees) {
        tree.draw();
    }
    // Render all ways
    for (const auto& way : ways) {
        way->draw();
    }
}

void Game::updateWays() {
    for (const auto& way : ways) {
        way->update();
    }
}