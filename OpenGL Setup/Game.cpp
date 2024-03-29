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
TextDisplayer* textdisplay;
GameObject coinSprite;

// Destructor
Game::~Game() {
    delete playerChar;
    delete textdisplay;
}

// Constructor
Game::Game() {}

// Initializes all instances
void Game::init()
{
    // Use current time as seed for random generator 
    srand(time(0));

    // Instanciate trees
    trees = {
        // Init trees
        Tree(-200.0, 350.0),
        Tree(-200.0, 750.0),
        Tree(-150.0, 300.0),
        Tree(-150.0, 550.0),
        Tree(-50.0, 400.0),
        Tree(50.0, 250.0),
        Tree(100.0, 700.0),
        Tree(150.0, 100.0),
        Tree(200.0, 350.0),
        Tree(300.0, 300.0)
    };

    // Load BG texture
    backgroundTex = TextureManager::instance()->getTexture("../OpenGL\ Setup/textures/ground.bmp");
   
    // Load coin sprite
    coinSprite = GameObject(-350, 250, 50, 50, "../OpenGL\ Setup/textures/coin.bmp");

    // Load text font
    textdisplay = new TextDisplayer("../OpenGL\ Setup/textures/fontMap.bmp", 7, 9, 18, 7, ' ');

    // Init paths and cars
    paths = {
        std::make_shared<Road>(125, VIEW_WIDTH),
        std::make_shared<River>(425, VIEW_WIDTH),
        std::make_shared<River>(675, VIEW_WIDTH),
    };

    // Instanciate player
    playerChar = new Character();

    // Update camera
    updateCamera();
}

// Draw all objects
void Game::drawScene()
{
    // Render BG
    glColor4ub(255, 255, 255, 255);  // Set color to white

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backgroundTex);

    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2f(-600, -600);
        glTexCoord2d(16.0, 0.0);
        glVertex2f(600, -600);
        glTexCoord2d(16, 16);
        glVertex2f(600, 1500);
        glTexCoord2d(0.0, 16);
        glVertex2f(-600, 1500);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, backgroundTex);
    glDisable(GL_TEXTURE_2D);

    // Render roads
    for (const auto& path : paths) {
        path->draw();
    }

    // Render player
    playerChar->draw();

    // Render all powerups
    for (const auto& powerup : collectibles) {
        powerup->draw();
    }

    // Render all trees
    for (const auto& tree : trees) {
        tree.draw();
    }

    // Render powerup bar
    if (activeShoes && activeShoes->time > 0) {
        activeShoes->drawBar(playerChar);
    }

    // Render score on screen
    textdisplay->drawScreen(std::to_string(score), 3, 0, 250, playerChar);

    // Render coins 
    coinSprite.drawFixed(playerChar);
    textdisplay->drawScreen(std::to_string(coins), 2, -310, 250, playerChar, false);
}

void Game::movePlayer(float deltaX, float deltaY)
{
    // Try to move 
    playerChar->move(deltaX, deltaY);
    // Check move would get us into a tree
    for (Tree& tree : trees) {
        // Cancel move if necessary
        if (playerChar->collidesWith(tree)) {
            playerChar->move(-deltaX, -deltaY);
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
        if (path->getsKilled(playerChar)) exit(0);
    }

    // Update collectibles
    // Generate new collectibles if there is room
    if(collectibles.size() <= MAX_COLLECTIBLES) spawnCollectibles();

    // Check for end of collectible presence and activation
    if (activeShoes && activeShoes->time > 0) activeShoes->update(DELTA_TIME, playerChar);
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
            std::cout << coinPtr << std::endl;
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