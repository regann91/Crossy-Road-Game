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
//TextDisplayer* textdisplay;
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
    flagEnd = std::make_shared<GameObject>(0, 1000, 21, 50, glm::vec4(0.6, 0.45, 0.4, 1));

    // Update camera
    updateCamera();
}


void Game::movePlayer(float deltaX, float deltaY)
{
    // Try to move 
    playerChar->move(deltaX, deltaY);

    // Check if the player collides with end flag
    if (playerChar->collidesWith(*flagEnd)) {
        // Print a congratulatory message
        std::cout << "Congratulations! You have reached the top!\n";

        // Exit the game
        exit(0);
    }

    // Check move would get us into a tree
    if (!cheatMode) {
        for (auto& tree : trees) {
            // Cancel move if necessary
            if (tree->collidesWith(*playerChar)) {
                playerChar->move(-deltaX, -deltaY);
            }
        }
    }
    // Update score
    if (deltaY > 0 && playerChar->y / playerChar->height > score)
        score = playerChar->y / playerChar->height;

    updateCamera();
}

// Updates the camera according to the Y player position
void Game::updateCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-VIEW_WIDTH / 2, VIEW_WIDTH / 2, -VIEW_HEIGHT / 2 + playerChar->y, VIEW_HEIGHT / 2 + playerChar->y);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

// Update function for game logic (e.g., character and car movement, collision detection)
void Game::update() {
    // Update all paths and check collisions (moving cars and trunks)
    for (const auto& path : paths) {
        path->update(DELTA_TIME);
        if (!cheatMode && path->getsKilled(playerChar.get())) {
            std::cout << "Oh no, your character has died! Your score was " << score << "! Rerun the program to play again :)\n";
            exit(0);
        }
    }

    // Update collectibles
    // Generate new collectibles if there is room
    if(collectibles.size() <= MAX_COLLECTIBLES) spawnCollectibles();

    // Check for end of collectible presence and activation
    if (activeShoes && activeShoes->time > 0) activeShoes->update(DELTA_TIME, playerChar.get());
    for (auto& collect : collectibles) {
        collect->update(DELTA_TIME, playerChar.get());
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


void Game::handleInput(char input) {
    if (input == 'p') {
        std::cout << "Cheat mode enabled" << std::endl;
        cheatMode = !cheatMode;
    }
}
