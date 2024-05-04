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
    void moveCamera(float dx, float dy, float dz);
    void rotateCamera(float dtheta, glm::vec3 axis);

private:
    // Private constructor
    Camera();

    // Single instance of manager
    static Camera* INSTANCE;

    // Viewing information and camera position
    glm::vec3 position;
    glm::vec3 offset;

    enum ViewingMode {
        THIRD_PERSON,
        FIRST_PERSON,
        SIDE_VIEW,
        ABOVE
    };
    ViewingMode viewMode;

    // World position of Camera (used for moving)
};