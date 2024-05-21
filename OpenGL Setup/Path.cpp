#include "Path.h"
#include <algorithm>  // Include the algorithm header for std::shuffle
#include <random>     // Include the random header for std::default_random_engine
#include "NormalMappedRenderable.h"

// Constructor implementation
Path::Path(float roadY, float roadZ, float roadWidth, glm::vec3 color, int nbObj, float objD, std::string tex, std::string normals)
    : GameObject(0, roadY, roadZ+50, roadWidth, 10, 100, color, 0, tex), nbObjPerLane(nbObj), objWidth(objD) {
    renderable = std::make_shared<NormalMappedRenderable>(*renderable.get(), normals);

    // CONSTRUCTION OF MESH
    // Ratio of terrain, used for texture mapping (total length of mesh/width of mesh)
    float ratio = 1.0 / 8.0;
    // Amount of texture tiles per width
    float tiles = 5;

    // Starting vertices
    std::vector<Vertex> vertices = {
        // Position                      // Color      // Tex Coord        // Normal
         Vertex(glm::vec3(-0.5, 0.5, -0.5), color, tiles * glm::vec2(0, 0), glm::vec3(0, 1, 0)),       // Bottom left
         Vertex(glm::vec3(0.5, 0.5, -0.5), color, tiles * glm::vec2(1, 0), glm::vec3(0, 1, 0)),        // Bottom right
         Vertex(glm::vec3(-0.5, 0.5, 0.5), color, tiles * glm::vec2(0, ratio), glm::vec3(0, 1, 0)),    // Top left
         Vertex(glm::vec3(0.5, 0.5, 0.5), color, tiles * glm::vec2(1, ratio), glm::vec3(0, 1, 0)),     // Top right
    };

    // One quad is composed of 4 vertices -> 6 indices
    std::vector<GLuint> indices = { 0,1,2,  1,2,3 };

    renderable->meshInfo = MeshManager::instance()->getMesh("path", vertices, indices);
}

void Path::createRoadMovingObj(float initX, float initZ, float speed) {
    movingObjects.emplace_back(
        MovingObject(initX, 18, initZ, objWidth, 50.0, 50, glm::vec3(1, 0.96, 1), speed, width, "carTex.bmp")
    );
    renderable->addChildRenderable(movingObjects.back().renderable);
}

void Path::createRiverMovingObj(float initX, float initZ, float speed) {
    movingObjects.emplace_back(
        MovingObject(initX, -11, initZ, objWidth, 20, 50.0, glm::vec3(1, 0.96, 1), speed, width, "trunkTex.bmp")
    );
    renderable->addChildRenderable(movingObjects.back().renderable);
}

void Path::initRoadMovingObjects() {
    const float baseSpacing = width / nbObjPerLane;  // Base spacing between cars

    // LANE GENERATION LOOP : 2 lanes
    for (int l = 0; l < 2; l++) {
        // Generate a single speed for the lane
        float laneSpeed = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 5.0 + 8.0;

        // Add cars to the road using randomized x positions and the same speed for the lane
        for (int i = 0; i < nbObjPerLane; ++i) {
            // Generate a random offset for the x position
            float offset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * baseSpacing - baseSpacing / 2;
            float initialX = i * baseSpacing + offset - width / 2; // Center on screen

            // Create and setup new obj
            createRoadMovingObj(initialX, z + (50.0 * l), laneSpeed * std::pow(-1, l));
        }

        // Shuffle the objects in the lane to further randomize their positions
        auto lane_begin = movingObjects.begin() + l * nbObjPerLane;
        auto lane_end = movingObjects.begin() + (l + 1) * nbObjPerLane;
        std::shuffle(lane_begin, lane_end, std::default_random_engine(std::random_device{}()));
    }
}

void Path::initRiverMovingObjects() {
    const float baseSpacing = width / nbObjPerLane;  // Base spacing between cars

    // LANE GENERATION LOOP : 2 lanes
    for (int l = 0; l < 2; l++) {
        // Generate a single speed for the lane
        float laneSpeed = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 5.0 + 8.0;

        // Add cars to the road using randomized x positions and the same speed for the lane
        for (int i = 0; i < nbObjPerLane; ++i) {
            // Generate a random offset for the x position
            float offset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * baseSpacing - baseSpacing / 2;
            float initialX = i * baseSpacing + offset - width / 2; // Center on screen
            createRiverMovingObj(initialX, z + (50.0 * l), laneSpeed * std::pow(-1, l));
        }

        // Shuffle the objects in the lane to further randomize their positions
        auto lane_begin = movingObjects.begin() + l * nbObjPerLane;
        auto lane_end = movingObjects.begin() + (l + 1) * nbObjPerLane;
        std::shuffle(lane_begin, lane_end, std::default_random_engine(std::random_device{}()));
    }
}

void Path::update(float deltaTime) {
    for (auto& obj : movingObjects) {
        obj.update(deltaTime * 0.001);  // Adjust the deltaTime as needed
    }
}

// Default behaviour
bool Path::getsKilled(std::shared_ptr<Character> player) {
    return false;
}