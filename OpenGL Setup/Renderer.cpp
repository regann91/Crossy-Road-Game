#include "Renderer.h"
#include <glm/geometric.hpp>

// Constructor implementation with initialized world (ground)
Renderer::Renderer() {
    renderingMode = COLOR;
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


void Renderer::toggleRenderingMode() {
    switch (renderingMode) {
    case COLOR:
        renderingMode = WIREFRAME;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_DEPTH_TEST);
        std::cout << "Current rendering mode: Wireframe (without depth removal)" << std::endl;
        break;
    case WIREFRAME:
        renderingMode = WIREFRAME_DEPTH_REMOVAL;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);
        std::cout << "Current rendering mode: Wireframe (with depth removal)" << std::endl;
        break;
    case WIREFRAME_DEPTH_REMOVAL:
        renderingMode = COLOR;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        std::cout << "Current rendering mode: Wireframe (with depth removal)" << std::endl;
        break;
    }
}


// Build world
void Renderer::buildWorld(Game& game) {
    
    // CONSTRUCT GROUND
    glm::vec3 color = glm::vec3(0.66, 0.53, 0.74);

    // Starting vertices
    std::vector<Vertex> vertGround = {
                // Position               // Color      // Tex Coord     // Normal
         Vertex(glm::vec3(-400, 0, -400), color, glm::vec2(0, 0), glm::vec3(0, 1, 0)),     // Bottom left
         Vertex(glm::vec3(400, 0, -400), color, glm::vec2(1, 0), glm::vec3(0, 1, 0)),      // Bottom right
    };

    // Iterate over the game paths to add vertices
    for (auto& path : game.paths) {
        // BEFORE THE PATH - Ground level (0)
        vertGround.emplace_back(glm::vec3(-400, 0, path->z - path->depth / 2), color, glm::vec2(0, 0), glm::vec3(0, 1, 0));
        vertGround.emplace_back(glm::vec3(400, 0, path->z - path->depth / 2), color, glm::vec2(0, 0), glm::vec3(0, 1, 0));

        // Path level (lower)
        vertGround.emplace_back(glm::vec3(-400, -20, path->z - path->depth / 2), color, glm::vec2(0, 0), glm::vec3(0, 0, 1));
        vertGround.emplace_back(glm::vec3(400, -20, path->z - path->depth / 2), color, glm::vec2(0, 0), glm::vec3(0, 0, 1));

        // AFTER THE PATH - Path level (lower)
        vertGround.emplace_back(glm::vec3(-400, -20, path->z + path->depth / 2), color, glm::vec2(0, 0), glm::vec3(0, 0, -1));
        vertGround.emplace_back(glm::vec3(400, -20, path->z + path->depth / 2), color, glm::vec2(0, 0), glm::vec3(0, 0, -1));

        // Ground level (0)
        vertGround.emplace_back(glm::vec3(-400, 0, path->z + path->depth / 2), color, glm::vec2(0, 0), glm::vec3(0, 1, 0));
        vertGround.emplace_back(glm::vec3(400, 0, path->z + path->depth / 2), color, glm::vec2(0, 0), glm::vec3(0, 1, 0));
    }

    // Ending vertices
    vertGround.emplace_back(glm::vec3(-400, 0, 1400), color, glm::vec2(0, 0), glm::vec3(0, 1, 0));
    vertGround.emplace_back(glm::vec3(400, 0, 1400), color, glm::vec2(0, 0), glm::vec3(0, 1, 0));


    // Iterate over the constructed vertices to build all of the triangles
    // One quad is composed of 4 vertices -> 6 indices
    std::vector<GLuint> indGround = {};

    for (unsigned int i = 0; i < vertGround.size() / 2 - 1; i++) {
        // FIRST QUAD
        indGround.insert(indGround.end(), { 2*i, 2*i+1, 2*i+2 });     // 1st triangle
        indGround.insert(indGround.end(), { 2*i+1, 2*i+2, 2*i+3 });   // 2nd triangle
    }

    ground = std::make_shared<Renderable>(MeshManager::instance()->getMesh("ground", vertGround, indGround));
}



// Draw all objects
void Renderer::drawScene(Game& game)
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