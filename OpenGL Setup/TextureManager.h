#pragma once
#include <map>
#include <vector>
#include <string>
#include <GL/freeglut.h>

class TextureManager {
public:
    // Constructor
    TextureManager();

    // Loads an openGL texture from a .bmp image file
    static GLuint loadTexture(const std::string& filename);
};