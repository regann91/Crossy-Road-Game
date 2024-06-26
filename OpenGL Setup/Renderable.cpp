#include "Renderable.h"
#include "TextureManager.h"
#include "Camera.h"
#include <iostream>
#include "Renderer.h"


// Constructor implementations
Renderable::Renderable(std::string pathMesh, glm::vec3 colorVec, std::string pathTex)
{
    // Load mesh, shader, set transformation to Id Matrix
    meshInfo = MeshManager::instance()->getMesh(pathMesh);
    phongShaderId = ShaderManager::instance()->getShader("phong", "phongVertex.glsl", "phongFragment.glsl");
    gouraudShaderId = ShaderManager::instance()->getShader("gouraud", "gouraudVertex.glsl", "gouraudFragment.glsl");
    texture = TextureManager::instance()->getTexture(pathTex);
    material = Material(colorVec * glm::vec3(0.35, 0.3, 0.40), colorVec, glm::vec3(0.3), 11.36);
    transform = glm::mat4(1);
}

// Manual mesh loading constructor
Renderable::Renderable(std::shared_ptr<Mesh> mesh, glm::vec3 colorVec, std::string pathTex)
{
    // Load mesh, shader, set transformation to Id Matrix
    meshInfo = mesh;
    phongShaderId = ShaderManager::instance()->getShader("phong","phongVertex.glsl","phongFragment.glsl");
    gouraudShaderId = ShaderManager::instance()->getShader("gouraud", "gouraudVertex.glsl", "gouraudFragment.glsl");
    texture = TextureManager::instance()->getTexture(pathTex);
    material = Material(colorVec * glm::vec3(0.35, 0.3, 0.40), colorVec, glm::vec3(0.3), 11.36);
    transform = glm::mat4(1);
}

// Draw implementation
void Renderable::draw() const {
    glPushMatrix();
    
    GLuint activeShader = Renderer::instance()->shadingType ? phongShaderId : gouraudShaderId;

    // Activate shader
    ShaderManager::bind(activeShader);

    // Send matrix info to buffer
    ShaderManager::instance()->setMat4(activeShader, "modelMat", transform);
    ShaderManager::instance()->setMat4(activeShader, "projMat", Camera::instance()->projectionMatrix);
    ShaderManager::instance()->setMat4(activeShader, "viewMat", Camera::instance()->viewMatrix);


    // Send lighting info to shader
    sendMaterialToShader(activeShader);
    Renderer::instance()->sendLightsToShader(activeShader);

    // Send texture info to shader
    ShaderManager::instance()->setBool(activeShader, "texturingActive", Renderer::instance()->texturing);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    ShaderManager::instance()->setInt(activeShader, "ground", 0);

    glBindVertexArray(meshInfo->buffer);
    glDrawElements(GL_TRIANGLES, meshInfo->indexNb, GL_UNSIGNED_INT, 0);

    // Draw all of the children renderables
    for (const auto& child : children) {
        child->draw();
    }
    // Unactivate
    ShaderManager::unbind();

    glPopMatrix();
}

// Function to add a child Renderable
void Renderable::addChildRenderable(std::shared_ptr<Renderable> r) {
    children.push_back(r);
}

// TRANSFORM FUNCS
void Renderable::setTransform(glm::mat4 trans) {
    transform = trans;
}

void Renderable::translate(float dx, float dy, float dz) {
    transform = glm::translate(transform, glm::vec3(dx, dy, dz));
}

void Renderable::rotate(float dtheta, glm::vec3 axis) {
    transform = glm::rotate(transform, dtheta, axis);
}

void Renderable::scale(float dw, float dh, float dd) {
    transform = glm::scale(transform, glm::vec3(dw, dh, dd));
}

glm::mat4 Renderable::getTrans(float x, float y, float z) {
    return glm::translate(glm::mat4(1), glm::vec3(x, y, z));
}

glm::mat4 Renderable::getRot(float theta, glm::vec3 axis) {
    return glm::rotate(glm::mat4(1), theta, axis);
}
glm::mat4 Renderable::getScale(float w, float h, float d) {
    return glm::scale(glm::mat4(1), glm::vec3(w, h, d));
}

void Renderable::sendMaterialToShader(GLuint activeShader) const {
    ShaderManager::instance()->setVec3(activeShader, "material.ambient", material.ambient);
    ShaderManager::instance()->setVec3(activeShader, "material.diffuse", material.diffuse);
    ShaderManager::instance()->setVec3(activeShader, "material.specular", material.specular);
    ShaderManager::instance()->setFloat(activeShader, "material.shininess", material.shininess);
}