#include "Road.h"
#include <random>
#include "NormalMappedRenderable.h"

// Constructor
Road::Road(float riverZ, float riverWidth)
    : Path(-12, riverZ, riverWidth, glm::vec3(1, 0.68, 0.83), 5, 50)
{
    initRoadMovingObjects();

    renderable = std::make_shared<NormalMappedRenderable>(*renderable.get());
    
    // CONSTRUCTION OF MESH
    auto color = glm::vec3(0);

    // Ratio of terrain, used for texture mapping (total length of mesh/width of mesh)
    float ratio = 1.0/8.0;
    // Amount of texture tiles per width
    float tiles = 5;

    // Starting vertices
    std::vector<Vertex> vertices = {
                // Position               // Color      // Tex Coord        // Normal
         Vertex(glm::vec3(-0.5, 0, -0.5), color, tiles * glm::vec2(0, 0), glm::vec3(0, 1, 0)),       // Bottom left
         Vertex(glm::vec3(0.5, 0, -0.5), color, tiles * glm::vec2(1, 0), glm::vec3(0, 1, 0)),        // Bottom right
         Vertex(glm::vec3(-0.5, 0, 0.5), color, tiles * glm::vec2(0, ratio), glm::vec3(0, 1, 0)),    // Top left
         Vertex(glm::vec3(0.5, 0, 0.5), color, tiles * glm::vec2(1, ratio), glm::vec3(0, 1, 0)),     // Top right
     };

    // One quad is composed of 4 vertices -> 6 indices
    std::vector<GLuint> indices = {0,1,2,  1,2,3};

    renderable->meshInfo = MeshManager::instance()->getMesh("road", vertices, indices);
}


bool Road::getsKilled(std::shared_ptr<Character> player) {
    // If player is on the road
    if(this->collidesWith(player)) {
        // Check for collision with cars
        for (auto& obj : movingObjects) {
            if (obj.collidesWith(player)) return true;
        }
    }
    return false;
}