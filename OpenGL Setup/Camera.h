#pragma once
#include <glm/glm.hpp>


// Singleton class that manages the drawing
class Camera {
public:
    // Matrices
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    // Deleting copy constructor
    Camera(const Camera& obj) = delete;

    // Returns the (single) instance of Camera
    static Camera* instance();

    void toggleViewMode();
    void updateCamera();

    // Allows to translate camera
    void moveCamera(float dx, float dy, float dz);          // Moves offset (depending on player)
    void moveCameraTo(float x, float y, float z);        // Sets offset (depending on player)
    void moveCameraOnInput(float dx, float dy, float dz);   // Moves position (player input)
    void resetInputOffset();
    void rotateCamera(float dtheta, glm::vec3 axis);        // Rotates (player input)

private:
    // Private constructor
    Camera();

    // Single instance of manager
    static Camera* INSTANCE;

    // Viewing information and camera position
    glm::vec3 position;     // Base position
    glm::vec3 offset;       // Player movement
    glm::vec3 offsetInput;   // Player input movement

    enum ViewingMode {
        THIRD_PERSON,
        FIRST_PERSON,
        SIDE_VIEW,
        ABOVE
    };
    ViewingMode viewMode;

    // World position of Camera (used for moving)
};