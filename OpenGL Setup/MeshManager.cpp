#include "MeshManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <map> 


// Default constructor implementation with empty map creation
MeshManager::MeshManager() {}

// Init to null
MeshManager* MeshManager::INSTANCE = NULL;

// Returns the (single) instance of ModelManager
MeshManager* MeshManager::instance()
{
    // Create and return instance if it doesnt exist
    if (INSTANCE == NULL) {
        INSTANCE = new MeshManager();
        return INSTANCE;
    }
    return INSTANCE;
}

// Gets a model from a filename
std::shared_ptr<Mesh> MeshManager::getMesh(std::string name) {
    // If already loaded in map, then return it
    auto it = loadedMeshes.find(name);
    if (it != loadedMeshes.end()) {
        return it->second;
    }
    // Else load it
    return loadMesh("../OpenGL\ Setup/models/" + name);
}

std::shared_ptr<Mesh> MeshManager::getMesh(std::string name, std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {

    auto it = loadedMeshes.find(name);
    if (it != loadedMeshes.end()) {
        return it->second;
    }

    auto mesh = std::make_shared<Mesh>(vertices, indices);

    loadedMeshes.emplace(name, mesh);
    return mesh;
}

// Load vertex info into buffers
std::shared_ptr<Mesh> MeshManager::loadMesh(std::string filename) {

    // Load texture
    //tex = TextureManager::loadTexture("../OpenGL\ Setup/textures/character.bmp");

    // New buffer for vertices
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    loadInfoFromFile(filename, vertices, indices);

    auto mesh = std::make_shared<Mesh>(vertices, indices);

    loadedMeshes.emplace(filename, mesh);
    return mesh;
        
}

void MeshManager::loadInfoFromFile(std::string filename, std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {

    // Vertex positions
    std::vector<glm::fvec3> vertPos;
    std::vector<glm::vec3> vertNorm;
    std::vector<glm::vec2> vertTexCoord;

    // Face vectors
    std::vector<GLuint> posIndices;
    std::vector<GLuint> normIndices;
    std::vector<GLuint> texCoordIndices;

    std::stringstream ss;
    std::ifstream file(filename);
    std::string line = "";
    std::string prefix = "";
    glm::vec3 tempVec3;
    glm::vec2 tempVec2;
    GLuint tempUint;

    // Opening ERROR check
    if (!file.is_open()) exit(0);

    // READ THE FILE AND LOAD INFO ONE LINE AT A TIME
    while (std::getline(file, line)) 
    {
        // Read line and get prefix
        ss.clear();
        ss.str(line);
        ss >> prefix;

        // VERTEX POSITION INFO
        if (prefix == "v") { 
            ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
            vertPos.push_back(tempVec3);
        }
        // VERTEX TEXTURE COORDINATE INFO
        else if (prefix == "vt") {
            ss >> tempVec2.x >> tempVec2.y;
            vertTexCoord.push_back(tempVec2);
        }
        // VERTEX NORMAL INFO
        else if (prefix == "vn") {
            ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
            vertNorm.push_back(tempVec3);
        }
        // FACE INFORMATION PROCESSING 
        else if (prefix == "f") {
            // Allows to know what info we are currently loading (Position/TexCoord/Normal)
            int counter = 0;
            while (ss >> tempUint) {
                // Pushing INFORMATION into correct array
                if (counter == 0) posIndices.push_back(tempUint);
                else if (counter == 1) texCoordIndices.push_back(tempUint);
                else if (counter == 2) normIndices.push_back(tempUint);

                // Handling OTHER CHARACTERS
                // If '/', then increment counter to load next vertex info
                if (ss.peek() == '/') {
                    counter = (counter + 1) % 3;
                    ss.ignore(1, '/');
                }
                // If ' ', then increment counter to load next vertex info
                else if (ss.peek() == ' ') {
                    counter = (counter + 1) % 3;
                    ss.ignore(1, ' ');
                }
            }
        }
    }
    // Build final vertex array 
    vertices.resize(vertPos.size(), Vertex());

    // Used for average computing
    std::vector<unsigned int> countEachVertex;
    countEachVertex.resize(vertPos.size(), 0);

    // Load in all vertices
    for (size_t i = 0; i < posIndices.size(); ++i) {
        vertices[posIndices[i] - 1].position = vertPos[posIndices[i]-1];
        vertices[posIndices[i] - 1].texCoord = vertTexCoord[texCoordIndices[i]-1];
        vertices[posIndices[i] - 1].normal += vertNorm[normIndices[i]-1];
        vertices[posIndices[i] - 1].color = glm::vec3(0);

        // Update count 
        countEachVertex[posIndices[i] - 1]++;
    }
    // Compute average of normal
    for (int i = 0; i < vertices.size(); i++) vertices[i].normal /= countEachVertex[i];

    // Build index 
    indices = posIndices;
    for (GLuint& i : indices) i--;
}

Vertex::Vertex(glm::vec3 pos, glm::vec3 col, glm::vec2 texC, glm::vec3 norm) {
    position = pos;
    color = col;
    texCoord = texC;
    normal = norm;
}

bool Vertex::operator==(const Vertex& other) const {
    return position == other.position;
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
    // New buffer for vertices
    GLuint VAO, VBO, EBO;

    // Generate new buffers - VBO is for vertices and EBO for indices
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object (buffer) first
    glBindVertexArray(VAO);

    // Bind and set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Configure vertex attributes
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);
    // Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    // Unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    buffer = VAO; indexNb = indices.size();
}