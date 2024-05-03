#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>


// Vertex struct for loading meshes
struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

struct Mesh {
    GLuint indexNb;
    GLuint buffer;
};

// Singleton class that manages the texture loading
class MeshManager {
public:
    // Deleting copy constructor
    MeshManager(const MeshManager& obj) = delete;

    // Returns the (single) instance of TextureManager
    static MeshManager* instance();

    // Returns a pointer to a model from the path
    std::shared_ptr<Mesh> getMesh(const std::string filename);

private:
    // Private constructor
    MeshManager();

    // Single instance of manager
    static MeshManager* INSTANCE;

    // Map of all already loaded textures with their path as the key
    std::map<const std::string, std::shared_ptr<Mesh>> loadedMeshes;

    // Loads buffers from .OBJ file
    std::shared_ptr<Mesh> loadMesh(const std::string filename);

    // Loads information from .OBJ file
    void loadInfoFromFile(std::string filename, std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
};