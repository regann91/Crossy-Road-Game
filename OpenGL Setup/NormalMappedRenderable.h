#pragma once
#include "Renderable.h"


class NormalMappedRenderable : public Renderable {
public:
    // Normal map info
    GLuint normalMap;

    // Constructor - default magenta
    NormalMappedRenderable(std::string pathMesh = "cube.obj", glm::vec3 colorVec = glm::vec4(1, 0, 1, 1), std::string pathTex = "groundTex.bmp", std::string pathNormal = "groundNormals.bmp");
    // Constructor with manually constructed mesh
    NormalMappedRenderable(std::shared_ptr<Mesh> mesh, glm::vec3 colorVec = glm::vec4(1, 0, 1, 1), std::string pathTex = "groundTex.bmp", std::string pathNormal = "groundNormals.bmp");
    // "Copy" constructor
    NormalMappedRenderable(Renderable&, std::string pathNormal = "groundNormals.bmp");

    // Function for drawing the object
    void draw() const final;
};