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

    Vertex(glm::vec3 pos = glm::vec3(0), glm::vec3 col = glm::vec3(0), glm::vec2 texC = glm::vec2(0), glm::vec3 norm = glm::vec3(0));
    bool operator==(const Vertex& other) const;
};

struct Mesh {
    GLuint indexNb;
    GLuint buffer;

    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
};

// Singleton class that manages the texture loading
class MeshManager {
public:
    // Deleting copy constructor
    MeshManager(const MeshManager& obj) = delete;

    // Returns the (single) instance of TextureManager
    static MeshManager* instance();

    // Returns a pointer to a mesh from the path
    std::shared_ptr<Mesh> getMesh(const std::string filename);

    // Creates mesh from data
    std::shared_ptr<Mesh> getMesh(std::string name, std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

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