#include "TextureManager.h"
#include <map>
#include <iostream>

// Default constructor implementation with empty map creation
TextureManager::TextureManager() {}

// Init to null
TextureManager* TextureManager::INSTANCE = NULL;

// Returns the (single) instance of TextureManager
TextureManager* TextureManager::instance() 
{
    // Create and return instance if it doesnt exist
    if(INSTANCE == NULL) {
        INSTANCE = new TextureManager();
        return INSTANCE;
    }
    return INSTANCE;
}

// Returns an openGL texture ID for the path
GLuint TextureManager::getTexture(const std::string filename) 
{
    // If texture is already loaded in map, then return it
    auto it = loadedTex.find(filename);
    if (it != loadedTex.end()) {
        return it->second;
    }
    // Else load it
    return loadTexture(filename);
}


// Loads an OpenGL texture ID from a filename
GLuint TextureManager::loadTexture(const std::string filename)
{
    GLuint texture;
    unsigned char* data;
    unsigned char R, G, B, A;
    unsigned char info[54];

    // Convert string to C char pointer
    const char* path = &filename[0];

    // Open .bmp image file
    FILE* filepoint;
    errno_t err;

    if ((err = fopen_s(&filepoint, path, "r")) != 0) {
        return 0;
    }

    // BMP Header info
    fread(info, sizeof(unsigned char), 54, filepoint);

    // Calculation of size from header info
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    // Reading of rest of data -> BMP image
    data = (unsigned char*)calloc(width * height * 4, sizeof(unsigned char));
    fread(data, sizeof(unsigned char), width * height * 4, filepoint);

    // End of reading
    fclose(filepoint);

    // transpose R, G, B values
    int index;
    for (int i = 0; i < width * height; ++i)
    {
        index = i * 4;
        B = data[index]; G = data[index + 1]; R = data[index + 2];
        A = ((int)R == 255 && (int)G == 0 && (int)B == 255) ? 0 : 255;
        data[index] = R; data[index + 1] = G; data[index + 2] = B; data[index + 3] = A;
    }

    // Create a texture
    // Gets new texture id
    glGenTextures(1, &texture);
    // Sets current working texture to new texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Parameters of texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Generation of texture from the data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


    // Free data in memory
    free(data);

    // Add texture to the map and return
    loadedTex.emplace(filename, texture);
    return texture;
}
