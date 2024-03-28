#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include "Character.h"

// Class that manages the text displaying for 1 font
class TextDisplayer {
public:
    TextDisplayer(std::string fontPath, int wChar, int hChar, int nbPerLine, int nbPerColumn, char first);

    // Draws text somewhere in the world
    void drawWorld(std::string text, float size, float x, float y) const;

    // Draws text fixed on screen, relatve to character position
    void drawScreen(std::string text, float size, float x, float y, Character* player) const;
   
private:
    // Bitmap font texture
    GLuint font;
    // Size of char on texture
    int widthChar, heightChar;
    // Number of chars on 1 line or column
    int nbCharPerLine, nbCharPerColumn;
    // First char on map
    char startChar;

    // Displays 1 character
    void drawChar(const char& character, float size, float x, float y) const;
};