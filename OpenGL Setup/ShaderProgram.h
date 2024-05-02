#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderProgram {
public:
    GLuint shaderId;   // Shader ID in memory

    // Constructor of shader
    ShaderProgram(std::string vertexPath, std::string fragmentPath);

    ShaderProgram() {};

    // Activate shader to draw
    void bind();

    // Disable current shader
    void static unbind();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec4(const std::string& name, float r, float g, float b, float a) const;
};