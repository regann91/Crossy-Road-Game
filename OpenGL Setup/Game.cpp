#pragma once
#include <time.h>
#include <iostream>

#include "TextureManager.h"
#include "TextDisplayer.h"
#include "Game.h"
#include "River.h"
#include "Road.h"
#include "Coin.h"


float RANDOM(float range = RAND_MAX) { return (float)rand() / (float)RAND_MAX * range; }
GameObject coinSprite;

// Constructor
Game::Game() : cheatMode(false) {}

// Initializes all instances
void Game::init()
{
    // Use current time as seed for random generator 
    srand(time(0));

    // Instanciate trees
    trees = {
        // Init trees
        std::make_shared<Tree>(-200.0, 350.0),
        std::make_shared<Tree>(-200.0, 800.0),
        std::make_shared<Tree>(-150.0, 300.0),
        std::make_shared<Tree>(-150.0, 550.0),
        std::make_shared<Tree>(-50.0, 400.0),
        std::make_shared<Tree>(50.0, 250.0),
        std::make_shared<Tree>(100.0, 650.0),
        std::make_shared<Tree>(150.0, 100.0),
        std::make_shared<Tree>(200.0, 350.0),
        std::make_shared<Tree>(300.0, 300.0)
    };
   
    // Load coin sprite
    

    // Load text font
    //textdisplay = new TextDisplayer("../OpenGL\ Setup/textures/fontMap.bmp", 7, 9, 18, 7, ' ');

    // Init paths and cars - all paths are 2 lanes wide (100 wide)
    // When rendering the ground, we will assume the paths are sorted 
    paths = {
        std::make_shared<Road>(125, VIEW_WIDTH),
        std::make_shared<River>(425, VIEW_WIDTH),
        std::make_shared<River>(675, VIEW_WIDTH),
    };

    // Instanciate player
    playerChar = std::make_shared<Character>();

    // Create end flag
    flagEnd = std::make_shared<GameObject>(0, 0, 1000, 10, 150, 10, glm::vec4(0.6, 0.45, 0.4, 1));
}


bool Game::movePlayer(float deltaX, float deltaZ)
{
    // Try to move 
    playerChar->move(deltaX, 0, deltaZ);

    // Check if the player collides with end flag
    if (flagEnd->collidesWith(playerChar)) {
        // Print a congratulatory message
        std::cout << "Congratulations! You have reached the top!\n";

        // Exit the game
        exit(0);
    }

    // Check if move would get us into a tree
    if (!cheatMode) {
        for (auto& tree : trees) {
            // Cancel move if necessary
            if (playerChar->collidesWith(tree)) {
                playerChar->move(-deltaX, 0, -deltaZ);
                return false;
            }
        }
    }
    // Move successful : update score
    if (deltaZ > 0 && playerChar->z / playerChar->depth > score)
        score = playerChar->z / playerChar->depth;

    return true;

}


// Update function for game logic (e.g., character and car movement, collision detection)
void Game::update() {
    // Update all paths and check collisions (moving cars and trunks)
    for (const auto& path : paths) {
        path->update(DELTA_TIME);
        if (!cheatMode && path->getsKilled(playerChar)) {
            std::cout << "Oh no, your character has died! Your score was " << score << "! Rerun the program to play again :)\n";
            exit(0);
        }
    }

    // Update collectibles
    // Generate new collectibles if there is room
    if(collectibles.size() <= MAX_COLLECTIBLES) spawnCollectibles();

    // Check for end of collectible presence and activation
    if (activeShoes && activeShoes->time > 0) activeShoes->update(DELTA_TIME, playerChar);          // Update shoes if still active
    else if (activeShoes && activeShoes->time < 0) {
        // Else notify player and delete
        std::cout << "Shoes expired! :(" << std::endl;
        activeShoes = nullptr;
    }

    // Iterate over list of collectibles to update them
    for (auto& collect : collectibles) {
        collect->update(DELTA_TIME, playerChar);
        // Check for collection
        if (collect->collected) {
            // IF SHOES
            auto shoePtr = std::dynamic_pointer_cast<Shoes>(collect);
            if (shoePtr != nullptr) {
                activeShoes = shoePtr; 
                break;
            }
            // IF COINS
            auto coinPtr = std::dynamic_pointer_cast<Coin>(collect);
            //std::cout << coinPtr << std::endl;
            if (coinPtr != nullptr) {
                coins++;
                std::cout << "Coin collected! Current amount is: " << coins << std::endl;
                break;
            }
        }
    }
    // Delete expired and activated powerups
    for (int i = 0; i < collectibles.size(); i++) {
        if (collectibles[i]->time < 0 || collectibles[i]->collected) {
            collectibles[i] = collectibles.back();
            collectibles.pop_back();
        }
    }
    // Update powerup effects
    playerChar->speed = activeShoes && activeShoes->time > 0 ? 2 : 1;
    glutPostRedisplay();
}

// Spawns powerup with a certain probability
void Game::spawnCollectibles() {
    int random = RANDOM() * RANDOM();

    // Spawn check
    if (random < Collectible::SPAWN_RATE && random > 0) {

        // Choose randomly between the different collectibles
        random = RANDOM();
        std::shared_ptr<Collectible> collectible;
        
        // Create random shoes in visible world (coins more frequent)
        switch (random % 3) {
            // Spawn shoes
        case 0: collectible = std::make_shared<Shoes>(
                RANDOM(VIEW_WIDTH) - VIEW_WIDTH / 2,
                RANDOM(VIEW_HEIGHT) - VIEW_HEIGHT / 2 + playerChar->y,
                Collectible::MAX_TIME
            );
                break;
        default: collectible = std::make_shared<Coin>(
                RANDOM(VIEW_WIDTH) - VIEW_WIDTH / 2,
                RANDOM(VIEW_HEIGHT) - VIEW_HEIGHT / 2 + playerChar->y,
                Collectible::MAX_TIME);
                break;
        }
        
        collectibles.push_back(collectible);
    }
}

void Game::toggleCheatMode() {
    cheatMode = !cheatMode;
}