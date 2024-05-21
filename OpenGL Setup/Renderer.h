#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <map>
#include <string>
#include "NormalMappedRenderable.h"
#include "GameObject.h"
#include "Game.h"
#include "Camera.h"

// Singleton class that manages the drawing
class Renderer {
public:

    // Deleting copy constructor
    Renderer(const Renderer& obj) = delete;

    // Returns the (sinzgle) instance of TextureManager
    static Renderer* instance();

    void buildWorld(Game& game);

    // Draws the scene
    void drawScene(Game& game);

    // Toggles between different rendering modes
    void toggleRenderingMode();

    void toggleShadingMode();
    void toggleNormalMapping();
    void toggleTexturing();

    // Send light info to a shader
    void sendLightsToShader(GLuint shaderId);

    void setShaderProgram(GLuint shaderId);

    // Lights
    struct DirectionalLight {
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        DirectionalLight(glm::vec3 pos = glm::vec3(1), glm::vec3 dir = glm::vec3(1), glm::vec3 amb = glm::vec3(1),
            glm::vec3 diff = glm::vec3(1), glm::vec3 spec = glm::vec3(1)) :
            position(pos), direction(dir), ambient(amb), diffuse(diff), specular(spec) {}

    } dirLight;

    struct PointLight {
        glm::vec3 position;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float constant;
        float linear;
        float quadratic;

        PointLight(glm::vec3 pos = glm::vec3(1), glm::vec3 amb = glm::vec3(1), glm::vec3 diff = glm::vec3(1),
            glm::vec3 spec = glm::vec3(1), float c = 1, float l = 0.1, float q = 0) :
            position(pos), ambient(amb), diffuse(diff), specular(spec), constant(c), linear(l), quadratic(q) {}

    } pointLight;

    // Shader mode (true is Phong/false is Gouraud)
    bool shadingType;
    // Texturing activated or not
    bool texturing;
    // Normal mapping activated or not
    bool normalMapping;

private:
    // Private constructor
    Renderer();

    // Single instance of manager
    static Renderer* INSTANCE;

    // Ground mesh
    std::shared_ptr<NormalMappedRenderable> ground;

    // Rendering mode
    enum RenderingMode {
        COLOR,
        WIREFRAME,
        WIREFRAME_DEPTH_REMOVAL
    };
    RenderingMode renderingMode;
};