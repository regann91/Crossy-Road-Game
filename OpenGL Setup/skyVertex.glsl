#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec4 vColor;

// Matrices
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

// Bottom color
vec4 bot = vec4(1, 0.68, 0.83, 1);

// Top color
vec4 top = vec4(0.62, 9.78, 0.91, 1);

void main()
{
    // Removing translation
    processedView = viewMat;
    for(int i = 0; i < 4; i++) {
        processedView[3][i] = 0;
        processedView[i][3] = 0;
    }
    
    gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0);

    if (position.x < 0) {
        vColor = bot;
    }
    else {
        vColor = y * top + (1-y) * bot;
    }
}