#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "ShaderManager.h"
#include "MeshManager.h"


class Renderable {
public:
    // Transformation
    glm::mat4 transform;

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

    // Transform funcs
    void setTransform(glm::mat4 trans);

    void translate(float dx, float dy, float dz);
    void rotate(float dtheta, glm::vec3 axis);
    void scale(float dw, float dh, float dd);

    static glm::mat4 getTrans(float x, float y, float z);
    static glm::mat4 getRot(float theta, glm::vec3 axis);
    static glm::mat4 getScale(float w, float h, float d);
};