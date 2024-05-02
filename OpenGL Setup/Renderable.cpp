#include "Renderable.h"
#include "TextureManager.h"
#include <iostream>

// Constructor implementation
Renderable::Renderable(float startX, float startY, float objWidth, float objHeight, std::string texpath)
    : x(startX), y(startY), width(objWidth), height(objHeight), rotation(0.0f)
{
    // Load texture
    tex = TextureManager::instance()->getTexture(texpath);
    loadNewBuffer();
}

// Draw implementation
void Renderable::draw() const {
    
    // draw our first triangle
    glUseProgram(shader->shaderId);

    shader->setVec4("colorVertex", 0.3, 0.8, 1, 1);
    glBindVertexArray(buffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glUseProgram(0);

    // Draw all of the children renderables
    for (const auto& child : children) {
        child->draw();
    }
}

// Draw fixed on screen (object to pass is character)
void Renderable::drawFixed(std::shared_ptr <Renderable> obj) const {
    glColor4ub(255, 255, 255, 255);  // Set color to white
    float posY = y + obj->y;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 0.0);
    glVertex2f(x - width / 2, posY - height / 2);
    glTexCoord2d(1.0, 0.0);
    glVertex2f(x + width / 2, posY - height / 2);
    glTexCoord2d(1.0, 1.0);
    glVertex2f(x + width / 2, posY + height / 2);
    glTexCoord2d(0.0, 1.0);
    glVertex2f(x - width / 2, posY + height / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Renderable::rotate(float speed) {
    rotation += speed;  // Increment the rotation angle

// Keep the rotation angle within [0, 360)
    if (rotation >= 360.0f) {
        rotation -= 360.0f;
    }
    else if (rotation < 0.0f) {
        rotation += 360.0f;
    }
}

void Renderable::setRotation(float newRotation) {
    rotation = newRotation;
}

void Renderable::rotateWithinRange(float speed, float deltaTime, float minRotation, float maxRotation) {
    rotation += speed * deltaTime;  // Increment the rotation angle

    // Keep the rotation angle within [minRotation, maxRotation)
    if (rotation >= maxRotation) {
        rotation -= (maxRotation - minRotation);
    }
    else if (rotation < minRotation) {
        rotation += (maxRotation - minRotation);
    }
}

// Function to add a child Renderable
void Renderable::addChildRenderable(std::shared_ptr<Renderable> r) {
    children.push_back(r);
}

// Load vertex info into buffers
void Renderable::loadNewBuffer() {

    // New buffer for vertices
    GLuint VBO, EBO;

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
    glGenVertexArrays(1, &buffer);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object (buffer) first
    glBindVertexArray(buffer);

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

}