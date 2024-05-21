#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include "Renderable.h"


class ShaderManager {
public:
    // Deleting copy constructor
    ShaderManager(const ShaderManager& obj) = delete;

    // Returns the (single) instance of ShaderManager
    static ShaderManager* instance();

    // Gets shader from name and/or path
    GLuint getShader(std::string name = "", std::string vertex = "", std::string fragment = "");

    // Activate shader to draw
    void static bind(GLuint id);

    // Disable current shader
    void static unbind();

    // Utility uniform functions
    void setBool(GLuint id, const std::string& name, bool value) const;
    void setInt(GLuint id, const std::string& name, int value) const;
    void setFloat(GLuint id, const std::string& name, float value) const;
    void setVec4(GLuint id, const std::string& name, const glm::vec4& color) const;
    void setVec3(GLuint id, const std::string& name, const glm::vec3& vec) const;
    void setMat4(GLuint id, const std::string& name, const glm::mat4& matrix) const;

    // Send view/projection matrices to shaders
    void sendMatrices(glm::mat4& proj, glm::mat4& view);

private:
    // Private constructor
    ShaderManager();

    // Single instance of manager
    static ShaderManager* INSTANCE;

    // Map of all already loaded textures with their name as the key
    std::map<const std::string, GLuint> loadedShaders;

    // Load information to the renderer
    GLuint loadShader(std::string name, std::string vertex, std::string fragment);

};