#include "Camera.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default constructor implementation
Camera::Camera() {
    viewMode = THIRD_PERSON;

    // Views
    projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(glm::vec3(-1, 1, -2), glm::vec3(1,0,4), glm::vec3(0.0f, 1.0f, 0.0f));
    //viewMatrix = glm::translate(glm::mat4(1), glm::vec3(-1,-0.5,0));
    //viewMatrix = glm::rotate(viewMatrix, 0.1f, glm::vec3(1,0,0));
}

// Init to null
Camera* Camera::INSTANCE = NULL;

// Returns the (single) instance of TextureManager
Camera* Camera::instance()
{
    // Create and return instance if it doesnt exist
    if (INSTANCE == NULL) {
        INSTANCE = new Camera();
        return INSTANCE;
    }
    return INSTANCE;
}

void Camera::toggleViewMode() {

}