#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec4.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "ShaderManager.h"
#include "MeshManager.h"
#include <glm/glm.hpp>

class Renderable {
public:
    // Transformation
    glm::mat4 model;

    // Information
    std::shared_ptr<Mesh> meshInfo;
    GLuint shaderId;
    glm::vec4 color;
    
    // Hierarchical children
    std::vector<std::shared_ptr<Renderable>> children;

    // Constructor - default magenta
    Renderable(glm::vec4 colorVec = glm::vec4(1,0,1,1), std::string path = "cube.obj");

    // Function for drawing the object
    void draw() const;

    // Function to add a child Renderable
    void addChildRenderable(std::shared_ptr<Renderable> r);
};