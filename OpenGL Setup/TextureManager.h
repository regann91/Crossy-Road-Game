#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <map>
#include <string>

// Singleton class that manages the texture loading
class TextureManager {
public:
    // Deleting copy constructor
    TextureManager(const TextureManager& obj) = delete;

    // Returns the (single) instance of TextureManager
    static TextureManager* instance();

    // Returns an openGL texture ID for the path
    GLuint getTexture(const std::string filename);

private:
    // Private constructor
    TextureManager();

    // Single instance of manager
    static TextureManager* INSTANCE;

    // Map of all already loaded textures with their path as the key
    std::map<const std::string, GLuint> loadedTex;

    // Loads an openGL texture from a .bmp image file
    GLuint loadTexture(const std::string filename);
};