#pragma once
#include "Game.h"
#include "River.h"
#include "Road.h"
#include "TextureManager.h"
#include <time.h>
#include <iostream>

float RANDOM(float range = RAND_MAX) { return (float)rand() / (float)RAND_MAX * range; }

// Destructor
Game::~Game() { 
    delete playerChar; 
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
    
    // Init paths and cars
    paths = {
        std::make_shared<Road>(125, VIEW_WIDTH),
        std::make_shared<Road>(425, VIEW_WIDTH),
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
    for (const auto& powerup : powerups) {
        powerup.draw();
    }

    // Render all trees
    for (const auto& tree : trees) {
        tree.draw();
    }

    // Render powerup bar
    if (activeShoes && activeShoes->time > 0) {
        activeShoes->drawBar(playerChar);
    }
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

    // Update powerups
    // Generate new powerup
    spawnPowerUps();

    // Check for end of powerup presence and activation
    if (activeShoes && activeShoes->time > 0) activeShoes->update(DELTA_TIME, playerChar);
    for (auto& powerup : powerups) {
        powerup.update(DELTA_TIME, playerChar);
        if (powerup.activated) activeShoes = std::make_shared<Shoes>(powerup);
    }

    // Delete expired and activated powerups
    for (int i = 0; i < powerups.size(); i++) {
        if (powerups[i].time < 0 || powerups[i].activated) {
            powerups[i] = powerups.back();
            powerups.pop_back();
        }
    }
    
    // Update powerup effects
    playerChar->speed = activeShoes && activeShoes->time > 0 ? 2 : 1;

    glutPostRedisplay();
}

// Spawns powerup with a certain probability
void Game::spawnPowerUps() {
    float random = RANDOM() * RANDOM();

    // Spawn shoes
    if (random < Shoes::SPAWN_RATE && random > 0) {
        // Create random shoes in visible world
        Shoes shoes = Shoes(
            RANDOM(VIEW_WIDTH) - VIEW_WIDTH / 2,
            RANDOM(VIEW_HEIGHT) - VIEW_HEIGHT / 2 + playerChar->y,
            Shoes::MAX_TIME
        );

        if(!playerChar->collidesWith(shoes)) powerups.push_back(shoes);
    }
}