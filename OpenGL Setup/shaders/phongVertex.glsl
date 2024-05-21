#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 elemPosition;
out vec3 elemNormal;
out vec2 elemTexCoord;

// Matrices
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 cameraPos;

void main()
{
    // All attributes are in world space
    elemPosition = vec3(modelMat * vec4(position, 1.0f));
    elemNormal = normal;
    elemTexCoord = texCoord;
    
    // Compute the position of the camera in world space
    cameraPos = - vec3( viewMat[3] ) * mat3( viewMat );
    
    // Define the fragment position on the screen
    gl_Position = projMat * viewMat * vec4(elemPosition, 1.0f);
}

