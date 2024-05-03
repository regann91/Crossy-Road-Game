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

// Color
uniform vec4 colorVertex;

// Light direction
vec3 light = normalize(vec3(-0.7,-1.1,-1));

// Shadow color
vec3 shadow = vec3(0.90, 0.85, 0.95);

vec4 clampVec4(vec4 vect, float min, float max) {
    vect.r = clamp(vect.r, min, max);
    vect.g = clamp(vect.g, min, max);
    vect.b = clamp(vect.b, min, max);
    vect.a = clamp(vect.a, min, max);

    return vect;
}

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(position, 1.0);

    float coeff = 1 - dot(light, normal);
    vec4 shadows = clampVec4(vec4(coeff * shadow,1), 0, 1);
    vColor = shadows * colorVertex;
}