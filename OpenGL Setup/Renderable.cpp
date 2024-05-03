#include "Renderable.h"
#include "TextureManager.h"
#include <iostream>

// Constructor implementation
Renderable::Renderable(glm::vec4 colorVec, std::string path)
{
    // Load mesh, shader, set transformation to Id Matrix
    meshInfo = MeshManager::instance()->getMesh(path);
    shaderId = ShaderManager::instance()->getShader();
    color = colorVec;
    model = glm::mat4(1);
}

// Draw implementation
void Renderable::draw() const {

    // Activate shader
    ShaderManager::bind(shaderId);

    // Draw from buffer
    ShaderManager::instance()->setVec4(shaderId, "colorVertex", color);
    glBindVertexArray(meshInfo->buffer);
    glDrawElements(GL_TRIANGLES, meshInfo->indexNb, GL_UNSIGNED_INT, 0);

    // Draw all of the children renderables
    for (const auto& child : children) {
        child->draw();
    }
    // Unactivate
    ShaderManager::unbind();
}

// Function to add a child Renderable
void Renderable::addChildRenderable(std::shared_ptr<Renderable> r) {
    children.push_back(r);
}