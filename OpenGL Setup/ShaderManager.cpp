#include "ShaderManager.h"
#include <glm/gtc/type_ptr.hpp>


// Private constructor - INITIALIZES SHADERS
ShaderManager::ShaderManager() {
    loadedShaders = {
        { "", getShader("", "flatVertex.glsl", "flatFragment.glsl") }
    };
}

// Init to null
ShaderManager* ShaderManager::INSTANCE = NULL;


// Returns the (single) instance of ShaderManager
ShaderManager* ShaderManager::instance()
{
    // Create and return instance if it doesnt exist
    if (INSTANCE == NULL) {
        INSTANCE = new ShaderManager();
        return INSTANCE;
    }
    return INSTANCE;
}

GLuint ShaderManager::getShader(std::string name, std::string vertex, std::string fragment) {
    // If already loaded in map, then return it
    auto it = loadedShaders.find(name);
    if (it != loadedShaders.end()) {
        return it->second;
    }
    // Else load it
    return loadShader(name, vertex, fragment);
}

GLuint ShaderManager::loadShader(std::string name, std::string vertexPath, std::string fragmentPath)
{
    // LOADING THE SHADERS
    // Load the vertex and fragment shaders from their respective paths
    std::string strVertex;
    std::string strFragment;
    std::ifstream fileVertex;
    std::ifstream fileFragment;

    // Sets Exception mask on to the ifstream objects
    fileVertex.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fileFragment.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Complete paths
    std::string vertexFullPath = "../OpenGL\ Setup/shaders/" + vertexPath;
    std::string fragmentFullPath = "../OpenGL\ Setup/shaders/" + fragmentPath;

    // Loading of code files into memory
    try
    {
        // Open the files
        fileVertex.open(vertexFullPath);
        fileFragment.open(fragmentFullPath);
        // Temp streams to read from the files
        std::stringstream vertexStream, fragmentStream;
        vertexStream << fileVertex.rdbuf();
        fragmentStream << fileFragment.rdbuf();
        // Close files
        fileVertex.close();
        fileFragment.close();
        // Convert streams to C++ strings
        strVertex = vertexStream.str();
        strFragment = fragmentStream.str();
    }
    // If fail during opening/reading of files
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    // Conversion of C++ string to C char pointer
    const char* vertexCode = strVertex.c_str();
    const char* fragmentCode = strFragment.c_str();

    // COMPILING THE SHADERS
    GLuint vertex, fragment;
    int success;
    GLchar infoLog[512];

    // Compiling Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Compiling Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // shader Program
    GLuint shaderId = glCreateProgram();
    glAttachShader(shaderId, vertex);
    glAttachShader(shaderId, fragment);
    glLinkProgram(shaderId);
    // print linking errors if any
    glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // Store in map
    loadedShaders.emplace(name, shaderId);
    return shaderId;
}

// BIND AND UNBIND
void ShaderManager::bind(GLuint id)
{
    glUseProgram(id);
}

void ShaderManager::unbind()
{
    glUseProgram(0);
}

// UTILITY UNIFORMS
void ShaderManager::sendMatrices(glm::mat4& proj, glm::mat4& view) {
    for (auto shader : loadedShaders) {
        std::cout << shader.second << std::endl;
        setMat4(shader.second, "projMat", proj);
        setMat4(shader.second, "viewMat", view);
    }
}


void ShaderManager::setBool(GLuint id, const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void ShaderManager::setInt(GLuint id, const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void ShaderManager::setFloat(GLuint id, const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderManager::setVec4(GLuint id, const std::string& name, const glm::vec4& color) const
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), color.r, color.g, color.b, color.a);
}

void ShaderManager::setVec3(GLuint id, const std::string& name, const glm::vec3& vec) const
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), vec.x, vec.y, vec.z);
}

void ShaderManager::setMat4(GLuint id, const std::string& name, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}