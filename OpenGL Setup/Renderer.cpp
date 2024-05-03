#include "Renderer.h"
#include <glm/geometric.hpp>

// Default constructor implementation with shader map init
Renderer::Renderer() {}

// Init to null
Renderer* Renderer::INSTANCE = NULL;

// Returns the (single) instance of TextureManager
Renderer* Renderer::instance()
{
    // Create and return instance if it doesnt exist
    if (INSTANCE == NULL) {
        INSTANCE = new Renderer();
        return INSTANCE;
    }
    return INSTANCE;
}

// Draw all objects
void Renderer::drawScene(Game game)
{
    // Render BG
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Send info to the shader

    // Render roads
    for (const auto& path : game.paths) {
        path->draw();
    }

    // Render player
    game.playerChar->draw();

    // Render all powerups
    for (const auto& powerup : game.collectibles) {
        powerup->draw();
    }

    // Render all trees
    for (const auto& tree : game.trees) {
        tree->draw();
    }

    // Render end flag
    game.flagEnd->draw();

    // Render powerup bar
    /*
    if (activeShoes && activeShoes->time > 0) {
        activeShoes->drawBar(playerChar);
    }

    // Render score on screen
    textdisplay->drawScreen(std::to_string(score), 3, 0, 250, playerChar);
    */

    // Render coins 
    //coinSprite.drawFixed(playerChar->renderable);
    //textdisplay->drawScreen(std::to_string(coins), 2, -310, 250, playerChar, false);

}