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

private:
    // Private constructor
    Camera();

    // Single instance of manager
    static Camera* INSTANCE;

    // Viewing information
    enum ViewingMode {
        THIRD_PERSON,
        FIRST_PERSON,
        SIDE_VIEW
    };
    ViewingMode viewMode;
};