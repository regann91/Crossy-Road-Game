#include "Camera.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/gtx/matrix_decompose.hpp>

float clamp(float nb, float min, float max) {
    return nb < min ? min : (nb > max ? max : nb);
}

// Default constructor implementation
Camera::Camera() {
    // Position
    position = glm::vec3(0);
    offset = glm::vec3(0);
    
    // View mode starts at THIRD PERSON
    projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1500.0f);
    viewMode = ABOVE;
    toggleViewMode();
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
    // Switching to FIRST PERSON
    if (viewMode == THIRD_PERSON) {
        viewMode = FIRST_PERSON;
        position = glm::vec3(0, 45, 25.1); 
        resetInputOffset();
        projectionMatrix = glm::perspective(glm::radians(50.0f), 800.0f / 600.0f, 0.1f, 1500.0f);
        std::cout << "Current viewing mode: First Person" << std::endl;
    }
    // Switching to SIDE VIEW
    else if (viewMode == FIRST_PERSON) {
        viewMode = SIDE_VIEW;
        position = glm::vec3(-425, 270, -70);
        resetInputOffset();
        projectionMatrix = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 0.1f, 1200.0f);
        std::cout << "Current viewing mode: Side View" << std::endl;
    }
    // Switching to ABOVE
    else if (viewMode == SIDE_VIEW) {
        viewMode = ABOVE;
        position = glm::vec3(0, 800, 0);
        resetInputOffset();
        projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1500.0f);
        std::cout << "Current viewing mode: Above" << std::endl;
    }
    // Switching to THIRD PERSON
    else if (viewMode == ABOVE) {
        viewMode = THIRD_PERSON;
        position = glm::vec3(0, 200, -200);
        resetInputOffset();
        projectionMatrix = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 1500.0f);
        std::cout << "Current viewing mode: Third Person" << std::endl;
    }
    updateCamera();
}

void Camera::moveCamera(float dx, float dy, float dz) {
    offset.x += dx;
    offset.y += dy;
    offset.z += dz;

    instance()->updateCamera();
}

void Camera::moveCameraTo(float x, float y, float z) {
    offset.x = x;
    offset.y = y;
    offset.z = z;

    instance()->updateCamera();
}

void Camera::moveCameraOnInput(float dx, float dy, float dz) {
    offsetInput.x += dx;
    offsetInput.y += dy;
    offsetInput.z += dz;

    instance()->updateCamera();
}

void Camera::resetInputOffset() {
    offsetInput = glm::vec3(0);
    updateCamera();
}

void Camera::updateCamera() {
    switch (viewMode) {
    case THIRD_PERSON:
        viewMatrix = glm::lookAt(
            position + glm::vec3(clamp(offset.x, -200, 200),0,offset.z) + offsetInput,
            glm::vec3(clamp(offset.x, -200, 200), 10, 100 + offset.z) + offsetInput,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        break;
    case FIRST_PERSON:
        viewMatrix = viewMatrix = glm::lookAt(
            position + glm::vec3(offset.x, 0, offset.z) + offsetInput,
            glm::vec3(offset.x, 40, 120 + offset.z) + offsetInput,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        break;
    case SIDE_VIEW:
        viewMatrix = glm::lookAt(
            position + glm::vec3(0, 0, offset.z) + offsetInput,
            glm::vec3(0, 60, 100 + offset.z) + offsetInput,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        break;
    case ABOVE:
        viewMatrix = glm::lookAt(
            position + glm::vec3(0, 0, offset.z) + offsetInput,
            glm::vec3(0, 0, offset.z) + offsetInput,
            glm::vec3(0.0f, 0.0f, 1.0f)
        );
        break;
    }
}

void Camera::rotateCamera(float dtheta, glm::vec3 axis) {
    viewMatrix = glm::translate(viewMatrix, position);
    viewMatrix = glm::rotate(viewMatrix, dtheta, axis);
    viewMatrix = glm::translate(viewMatrix, position);
}