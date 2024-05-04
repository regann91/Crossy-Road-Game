#include "Renderer.h"
#include <glm/geometric.hpp>

// Constructor implementation with initialized world (ground)
Renderer::Renderer() {

    // Construct world (ground)
    std::vector<Vertex> vertGround = {
              // Position                // Color                    // Tex Coord    // Normal
        Vertex(glm::vec3(-0.5, 0, -0.5), glm::vec3(0.66, 0.53, 0.74), glm::vec2(0, 0), glm::vec3(0, 1, 0)),     // Bottom left
        Vertex(glm::vec3(0.5, 0, -0.5), glm::vec3(0.66, 0.53, 0.74), glm::vec2(1, 0), glm::vec3(0, 1, 0)),      // Bottom right
        Vertex(glm::vec3(0.5, 0, 0.5), glm::vec3(0.66, 0.53, 0.74), glm::vec2(1, 1), glm::vec3(0, 1, 0)),       // Top right
        Vertex(glm::vec3(-0.5, 0, 0.5), glm::vec3(0.66, 0.53, 0.74), glm::vec2(0, 0), glm::vec3(0, 1, 0)),      // Top left
    };

    std::vector<GLuint> indGround = { 
        0, 1, 2,  // first Triangle
        0, 2, 3   // second Triangle
    };

    ground = std::make_shared<Renderable>(MeshManager::instance()->getMesh("ground", vertGround, indGround));
}

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
    // Draw ground
    glClearColor(0.62, 0.78, 0.91, 1);
    ground->draw();

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