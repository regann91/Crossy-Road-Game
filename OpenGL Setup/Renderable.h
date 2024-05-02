#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "ShaderProgram.h"
#include "glm/vec4.hpp"

class Renderable {
public:
    float x, y;  // Position
    float width, height;  // Dimensions
    float rotation;
    GLuint tex;   // Texture
    std::shared_ptr<ShaderProgram> shader;   // Shader
    unsigned int buffer;

    std::vector<std::shared_ptr<Renderable>> children;

    // Constructor
    Renderable(float startX, float startY, float objWidth, float objHeight, std::string texpath);

    // Constructor
    Renderable() {}

    // Function for drawing the object
    void draw() const;

    // Function for drawing the object in a fixed place on screen (relative to character position)
    void drawFixed(std::shared_ptr<Renderable> obj) const;

    // Function to add a child Renderable
    void addChildRenderable(std::shared_ptr<Renderable> r);

    virtual void rotate(float speed);

    void setRotation(float newRotation);

    void rotateWithinRange(float speed, float deltaTime, float minRotation, float maxRotation);

private:
    // Loads the vertex information into a buffer
    void loadNewBuffer();
};