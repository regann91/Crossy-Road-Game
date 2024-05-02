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
std::shared_ptr<ShaderProgram> flatShader;

// Destructor
Game::~Game() {
    delete playerChar;
    delete textdisplay;
    delete flagEnd;
}

// Constructor
Game::Game() : cheatMode(false) {}

// Initializes all instances
void Game::init()
{
    // Use current time as seed for random generator 
    srand(time(0));

    // Load shader
    flatShader = std::make_shared<ShaderProgram>("../OpenGL\ Setup/shaders/flatVertex.glsl", "../OpenGL\ Setup/shaders/flatFragment.glsl");

    // Instanciate trees
    trees = {
        // Init trees
        Tree(-200.0, 350.0),
        Tree(-200.0, 800.0),
        Tree(-150.0, 300.0),
        Tree(-150.0, 550.0),
        Tree(-50.0, 400.0),
        Tree(50.0, 250.0),
        Tree(100.0, 650.0),
        Tree(150.0, 100.0),
        Tree(200.0, 350.0),
        Tree(300.0, 300.0)
    };

    // Load BG texture
    backgroundTex = TextureManager::instance()->getTexture("../OpenGL\ Setup/textures/ground.bmp");
   
    // Load coin sprite
    coinSprite = GameObject(-350, 250, 50, 50, "../OpenGL\ Setup/textures/coin.bmp");
    coinSprite.renderable->shader = flatShader;

    // Load text font
    textdisplay = new TextDisplayer("../OpenGL\ Setup/textures/fontMap.bmp", 7, 9, 18, 7, ' ');

    // Init paths and cars - all paths are 2 lanes wide (100 wide)
    // When rendering the ground, we will assume the paths are sorted 
    paths = {
        std::make_shared<Road>(125, VIEW_WIDTH),
        std::make_shared<River>(425, VIEW_WIDTH),
        std::make_shared<River>(675, VIEW_WIDTH),
    };

    for (auto& path : paths) {
        path->renderable->shader = flatShader;
        for (auto& obj : path->renderable->children) {
            obj->shader = flatShader;
        }
    }

    for (auto& tree : trees) {
        tree.renderable->shader = flatShader;
    }

    // Instanciate player
    playerChar = new Character();
    playerChar->renderable->shader = flatShader;

    // Create end flag
    flagEnd = new GameObject(0, 1000, 21, 50, "../OpenGL\ Setup/textures/flag.bmp");
    flagEnd->renderable->shader = flatShader;

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
        tree.renderable->draw();
    }

    // Render powerup bar
    if (activeShoes && activeShoes->time > 0) {
        activeShoes->drawBar(playerChar);
    }

    // Render score on screen
    textdisplay->drawScreen(std::to_string(score), 3, 0, 250, playerChar);

    // Render end flag
    flagEnd->draw();

    // Render coins 
    coinSprite.drawFixed(playerChar->renderable);
    textdisplay->drawScreen(std::to_string(coins), 2, -310, 250, playerChar, false);
   
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
        for (Tree& tree : trees) {
            // Cancel move if necessary
            if (playerChar->collidesWith(tree)) {
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
        if (!cheatMode && path->getsKilled(playerChar)) {
            std::cout << "Oh no, your character has died! Your score was " << score << "! Rerun the program to play again :)\n";
            exit(0);
        }
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
        collectible->renderable->shader = flatShader;
    }
}


void Game::handleInput(char input) {
    if (input == 'p') {
        std::cout << "Cheat mode enabled" << std::endl;
        cheatMode = !cheatMode;
    }
}
