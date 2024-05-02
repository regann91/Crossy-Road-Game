#include "Renderable.h"
#include "TextureManager.h"
#include <iostream>

// Constructor implementation
Renderable::Renderable(glm::vec4 colorVec, std::string path)
{
    // Load model, shader, set transformation to Id Matrix
    model = ModelManager::instance()->getModel(path);
    shaderId = ShaderManager::instance()->getShader();
    color = colorVec;
    transformation = glm::mat4(1);
}

// Draw implementation
void Renderable::draw() const {
    
    // Activate shader
    ShaderManager::bind(shaderId);

    // Draw from buffer
    ShaderManager::instance()->setVec4(shaderId, "colorVertex", color);
    glBindVertexArray(model->vertices);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Unactivate
    ShaderManager::unbind();

    // Draw all of the children renderables
    for (const auto& child : children) {
        child->draw();
    }
}

// Function to add a child Renderable
void Renderable::addChildRenderable(std::shared_ptr<Renderable> r) {
    children.push_back(r);
}