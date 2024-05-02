#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <map>
#include <string>
#include <memory>

// Model class to represent the buffers
class Model {
public:
    GLuint vertices;

    Model(GLuint v) { vertices = v; }
};

// Singleton class that manages the texture loading
class ModelManager {
public:
    // Deleting copy constructor
    ModelManager(const ModelManager& obj) = delete;

    // Returns the (single) instance of TextureManager
    static ModelManager* instance();

    // Returns a pointer to a model from the path
    std::shared_ptr<Model> getModel(const std::string filename);

    // Returns the vertices id of model

private:
    // Private constructor
    ModelManager();

    // Single instance of manager
    static ModelManager* INSTANCE;

    // Map of all already loaded textures with their path as the key
    std::map<const std::string, std::shared_ptr<Model>> loadedModels;

    // Loads an openGL texture from a .bmp image file
    std::shared_ptr<Model> loadModel(const std::string filename);
};