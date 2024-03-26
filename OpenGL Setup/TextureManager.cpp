#include "TextureManager.h"
#include <map>
#include <iostream>

// Constructor
TextureManager::TextureManager() {}

// Loads an openGL texture from a .bmp image file
GLuint TextureManager::loadTexture(const std::string& filename)
{
    GLuint texture;
    unsigned char* data;
    unsigned char R, G, B;
    unsigned char info[54];

    // Open .bmp image file
    FILE* filepoint;
    errno_t err;

    // Conversion from cpp string to c char*
    const char* path = filename.c_str();

    if ((err = fopen_s(&filepoint, path, "r")) != 0) {
        return 0;
    }

    // BMP Header info
    fread(info, sizeof(unsigned char), 54, filepoint);

    // Calculation of size from header info
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    // Reading of rest of data -> BMP image
    data = (unsigned char*)calloc(width * height * 3, sizeof(unsigned char));
    fread(data, sizeof(unsigned char), width * height * 3, filepoint);

    // End of reading
    fclose(filepoint);

    // transpose R, G, B values
    int index;
    for (int i = 0; i < width * height; ++i)
    {
        index = i * 3;
        B = data[index]; G = data[index + 1]; R = data[index + 2];
        data[index] = R; data[index + 1] = G; data[index + 2] = B;
    }

    // Create a texture
    // Gets new texture id
    glGenTextures(1, &texture);
    // Sets current working texture to new texture
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, texture);

    // Parameters of texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Generation of texture from the data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);


    // Free data in memory
    free(data);
    return texture;
}