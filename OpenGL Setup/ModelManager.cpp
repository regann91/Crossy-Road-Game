#include "ModelManager.h"
#include <map>
#include <iostream>

// Default constructor implementation with empty map creation
ModelManager::ModelManager() {}

// Init to null
ModelManager* ModelManager::INSTANCE = NULL;

// Returns the (single) instance of TextureManager
ModelManager* ModelManager::instance()
{
    // Create and return instance if it doesnt exist
    if (INSTANCE == NULL) {
        INSTANCE = new ModelManager();
        return INSTANCE;
    }
    return INSTANCE;
}

std::shared_ptr<Model> ModelManager::getModel(std::string name) {
    // If already loaded in map, then return it
    auto it = loadedModels.find(name);
    if (it != loadedModels.end()) {
        return it->second;
    }
    // Else load it
    return loadModel(name);
}

// Load vertex info into buffers
std::shared_ptr<Model> ModelManager::loadModel(std::string name) {

    // New buffer for vertices
    GLuint VBO, EBO;
    // Buffer id
    GLuint bufferId;

    // Square
    float vertices[] = {
         0.5,  0.5, 0.0f,  // top right
         0.5, -0.5, 0.0f,  // bottom right
        -0.5, -0.5, 0.0f,  // bottom left
        -0.5, 0.5, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    // Generate new buffers - VBO is for vertices and EBO for indices
    glGenVertexArrays(1, &bufferId);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object (buffer) first
    glBindVertexArray(bufferId);

    // Bind and set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Configure vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Return model
    auto model = std::make_shared<Model>(bufferId);
    loadedModels.emplace(name, model);
    return model;
}