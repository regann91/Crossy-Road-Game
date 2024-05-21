#include "Renderable.h"
#include "TextureManager.h"
#include "Camera.h"
#include <iostream>
#include "Renderer.h"

// Constructor implementations
Renderable::Renderable(glm::vec3 colorVec, std::string path)
{
    // Load mesh, shader, set transformation to Id Matrix
    meshInfo = MeshManager::instance()->getMesh(path);
    //shaderId = ShaderManager::instance()->getShader("phong", "phongVertex.glsl", "phongFragment.glsl");
    shaderId = ShaderManager::instance()->getShader("gouraud", "gouraudVertex.glsl", "gouraudFragment.glsl");
    //if (shadingMode) {
    //    shaderId = ShaderManager::instance()->getShader("phong", "phongVertex.glsl", "phongFragment.glsl");
    //}
    //else {
    //    shaderId = ShaderManager::instance()->getShader("gouraud", "gouraudVertex.glsl", "gouraudFragment.glsl");
    //}
    material = Material(colorVec * glm::vec3(0.35, 0.3, 0.40), colorVec, glm::vec3(0.3), 11.36);
    transform = glm::mat4(1);
}

// Manual mesh loading constructor
Renderable::Renderable(std::shared_ptr<Mesh> mesh)
{
    // Load mesh, shader, set transformation to Id Matrix
    meshInfo = mesh;
    //shaderId = ShaderManager::instance()->getShader("phong","phongVertex.glsl","phongFragment.glsl");
    shaderId = ShaderManager::instance()->getShader("gouraud", "gouraudVertex.glsl", "gouraudFragment.glsl");
    //if (shadingMode) {
    //    shaderId = ShaderManager::instance()->getShader("phong", "phongVertex.glsl", "phongFragment.glsl");
    //}
    //else {
    //    shaderId = ShaderManager::instance()->getShader("gouraud", "gouraudVertex.glsl", "gouraudFragment.glsl");
    //}
    material = Material(glm::vec3(0.35, 0.3, 0.40), glm::vec3(1), glm::vec3(0.3), 11.36);
    transform = glm::mat4(1);
}

// Draw implementation
void Renderable::draw() const {
    glPushMatrix();
    // Activate shader
    ShaderManager::bind(shaderId);

    // Send matrix info to buffer
    ShaderManager::instance()->setMat4(shaderId, "modelMat", transform);
    ShaderManager::instance()->setMat4(shaderId, "projMat", Camera::instance()->projectionMatrix);
    ShaderManager::instance()->setMat4(shaderId, "viewMat", Camera::instance()->viewMatrix);


    // Send lighting info to shader
    sendMaterialToShader();
    Renderer::instance()->sendLightsToShader(shaderId);

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

void Renderable::sendMaterialToShader() const {
    ShaderManager::instance()->setVec3(shaderId, "material.ambient", material.ambient);
    ShaderManager::instance()->setVec3(shaderId, "material.diffuse", material.diffuse);
    ShaderManager::instance()->setVec3(shaderId, "material.specular", material.specular);
    ShaderManager::instance()->setFloat(shaderId, "material.shininess", material.shininess);
}