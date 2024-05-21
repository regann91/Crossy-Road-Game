#include "NormalMappedRenderable.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Renderer.h"

// Constructor implementations
NormalMappedRenderable::NormalMappedRenderable(std::string pathMesh, glm::vec3 colorVec, std::string pathTex, std::string pathNormal) 
    : Renderable(pathMesh, colorVec, pathTex)
{
    // Load normals info
    normalMapShaderId = ShaderManager::instance()->getShader("normalMappedPhong", "normalMappedPhongVertex.glsl", "normalMappedPhongFragment.glsl");
    normalMap = TextureManager::instance()->getTexture(pathNormal);
}

// Manual mesh loading constructor
NormalMappedRenderable::NormalMappedRenderable(std::shared_ptr<Mesh> mesh, glm::vec3 colorVec, std::string pathTex, std::string pathNormal) 
    : Renderable(mesh, colorVec, pathTex)
{
    // Load normals info
    normalMapShaderId = ShaderManager::instance()->getShader("normalMappedPhong", "normalMappedPhongVertex.glsl", "normalMappedPhongFragment.glsl");
    normalMap = TextureManager::instance()->getTexture(pathNormal);
}

NormalMappedRenderable::NormalMappedRenderable(Renderable& renderable, std::string pathNormal)
    : Renderable(renderable)
{
    // Load normals info
    normalMapShaderId = ShaderManager::instance()->getShader("normalMappedPhong", "normalMappedPhongVertex.glsl", "normalMappedPhongFragment.glsl");
    normalMap = TextureManager::instance()->getTexture(pathNormal);
}

/*
// Transformation
    glm::mat4 transform;

    // Information
    std::shared_ptr<Mesh> meshInfo;
    GLuint shaderId;
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
*/

// Draw implementation
void NormalMappedRenderable::draw() const {
    glPushMatrix();

    GLuint activeShader = normalMapShaderId;

    // Activate shader
    ShaderManager::bind(activeShader);

    // Send matrix info to buffer
    ShaderManager::instance()->setMat4(activeShader, "modelMat", transform);
    ShaderManager::instance()->setMat4(activeShader, "projMat", Camera::instance()->projectionMatrix);
    ShaderManager::instance()->setMat4(activeShader, "viewMat", Camera::instance()->viewMatrix);

    // Send lighting info to shader
    Renderable::sendMaterialToShader();
    Renderer::instance()->sendLightsToShader(activeShader);

    // Send texture info to shader
    ShaderManager::instance()->setInt(normalMapShaderId, "tex", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    ShaderManager::instance()->setInt(normalMapShaderId, "normals", 1);
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