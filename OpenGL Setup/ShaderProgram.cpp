#include "ShaderProgram.h"

// Constructor of shader
ShaderProgram::ShaderProgram(std::string vertexPath, std::string fragmentPath)
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

    // Loading of code files into memory
    try
    {
        // Open the files
        fileVertex.open(vertexPath);
        fileFragment.open(fragmentPath);
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
    char infoLog[512];

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
    shaderId = glCreateProgram();
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
}

void ShaderProgram::bind()
{
    glUseProgram(shaderId);
}


void ShaderProgram::unbind()
{
    glUseProgram(0);
}

void ShaderProgram::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);
}
void ShaderProgram::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
}
void ShaderProgram::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
}

void ShaderProgram::setVec4(const std::string& name, float r, float g, float b, float a) const
{
    glUniform4f(glGetUniformLocation(shaderId, name.c_str()), r, g, b, a);
}