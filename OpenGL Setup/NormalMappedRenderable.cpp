#include "NormalMappedRenderable.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Renderer.h"

// Constructor implementations
NormalMappedRenderable::NormalMappedRenderable(std::string pathMesh, glm::vec3 colorVec, std::string pathTex, std::string pathNormal) 
    : Renderable(pathMesh, colorVec, pathTex)
{
    // Load normals info
    phongShaderId = ShaderManager::instance()->getShader("normalMappedPhong", "normalMappedPhongVertex.glsl", "normalMappedPhongFragment.glsl");
    normalMap = TextureManager::instance()->getTexture(pathNormal);
}

// Manual mesh loading constructor
NormalMappedRenderable::NormalMappedRenderable(std::shared_ptr<Mesh> mesh, glm::vec3 colorVec, std::string pathTex, std::string pathNormal) 
    : Renderable(mesh, colorVec, pathTex)
{
    // Load normals info
    phongShaderId = ShaderManager::instance()->getShader("normalMappedPhong", "normalMappedPhongVertex.glsl", "normalMappedPhongFragment.glsl");
    normalMap = TextureManager::instance()->getTexture(pathNormal);
}

NormalMappedRenderable::NormalMappedRenderable(Renderable& renderable, std::string pathNormal)
    : Renderable(renderable)
{
    // Load normals info
    phongShaderId = ShaderManager::instance()->getShader("normalMappedPhong", "normalMappedPhongVertex.glsl", "normalMappedPhongFragment.glsl");
    normalMap = TextureManager::instance()->getTexture(pathNormal);
}

// Draw implementation
void NormalMappedRenderable::draw() const {
    glPushMatrix();

    GLuint activeShader = Renderer::instance()->shadingType ? phongShaderId : gouraudShaderId;

    // Activate shader
    ShaderManager::bind(activeShader);

    // Send matrix info to buffer
    ShaderManager::instance()->setMat4(activeShader, "modelMat", transform);
    ShaderManager::instance()->setMat4(activeShader, "projMat", Camera::instance()->projectionMatrix);
    ShaderManager::instance()->setMat4(activeShader, "viewMat", Camera::instance()->viewMatrix);

    // Send lighting info to shader
    Renderable::sendMaterialToShader(activeShader);
    Renderer::instance()->sendLightsToShader(activeShader);

    // Send texture info to shader
    ShaderManager::instance()->setBool(activeShader, "texturingActive", Renderer::instance()->texturing);
    ShaderManager::instance()->setInt(activeShader, "tex", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Normal map info
    ShaderManager::instance()->setBool(activeShader, "normalMappingActive", Renderer::instance()->normalMapping);
    ShaderManager::instance()->setInt(activeShader, "normals", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalMap);

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