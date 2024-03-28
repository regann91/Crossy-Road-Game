#include "TextDisplayer.h"
#include "TextureManager.h"


TextDisplayer::TextDisplayer(std::string fontPath, int wChar, int hChar, int nbPerLine, int nbPerCol, char first)
	: widthChar(wChar), heightChar(hChar), nbCharPerLine(nbPerLine), nbCharPerColumn(nbPerCol), startChar(first) {
	// Load font
	font = TextureManager::instance()->getTexture(fontPath);
}

// Draws text somewhere in the world
void TextDisplayer::drawWorld(std::string text, float size, float x, float y, bool centered) const {
    glColor4ub(255, 255, 255, 255);  // Set color to white

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, font);

    // Start drawing all characters from string
    glBegin(GL_QUADS);

    float posX = centered ? x - size * widthChar * text.length() / 2 : x;
    for (const auto& ch : text) {
        drawChar(ch, size, posX, y);
        posX += widthChar;
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Draws text fixed on screen, relatve to character position
void TextDisplayer::drawScreen(std::string text, float size, float x, float y, Character* player, bool centered) const {
    //std::cout << x << "     " << y << std::endl;
    glColor4ub(255, 255, 255, 255);  // Set color to white

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, font);

    // Start drawing all characters from string
    glBegin(GL_QUADS);

    float posX = centered ? x - size * widthChar * text.length() / 2 : x;
    float posY = y + player->y;
    for (const auto& ch : text) {
        drawChar(ch, size, posX, posY);
        posX += size*widthChar;
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Draws centered char
void TextDisplayer::drawChar(const char& character, float size, float x, float y) const {
    // Compute texture coordinates
    
    int charNum = character - startChar;
    float column = charNum % nbCharPerLine; // Remainder of euclidian division : num of column from left
    float row = (int) (nbCharPerColumn - 1 - charNum / nbCharPerLine); // Quotient of division : num of row from bottom

    glTexCoord2d(column/nbCharPerLine, row / nbCharPerColumn);
    glVertex2f(x - size * widthChar / 2, y - size * heightChar / 2);

    glTexCoord2d((column+1) / nbCharPerLine, row / nbCharPerColumn);
    glVertex2f(x + size * widthChar / 2, y - size * heightChar / 2);

    glTexCoord2d((column+1) / nbCharPerLine, (row + 1) / nbCharPerColumn);
    glVertex2f(x + size * widthChar / 2, y + size * heightChar / 2);

    glTexCoord2d(column / nbCharPerLine, (row + 1) / nbCharPerColumn);
    glVertex2f(x - size * widthChar / 2, y + size * heightChar / 2);
}