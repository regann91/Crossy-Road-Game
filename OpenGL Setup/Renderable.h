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
    GLuint phongShaderId, gouraudShaderId;
    GLuint texture;

    // Material
    struct Material {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

        Material(glm::vec3 amb = glm::vec3(1), glm::vec3 diff = glm::vec3(1), glm::vec3 spec = glm::vec3(1), float shine = 10)
            : ambient(amb), diffuse(diff), specular(spec), shininess(shine) {}

    } material;
    
    // Hierarchical children
    std::vector<std::shared_ptr<Renderable>> children;

    // Constructor - default magenta
    Renderable(std::string pathMesh = "cube.obj", glm::vec3 colorVec = glm::vec4(1, 0, 1, 1), std::string pathTex = "texx.bmp");
    // Constructor with manually constructed mesh
    Renderable(std::shared_ptr<Mesh> mesh, glm::vec3 colorVec = glm::vec4(1, 0, 1, 1), std::string pathTex = "texx.bmp");

    // Function for drawing the object
    virtual void draw() const;
    void sendMaterialToShader(GLuint activeShader) const;

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