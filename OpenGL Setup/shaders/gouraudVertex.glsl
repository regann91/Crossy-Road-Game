#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec3 elemColor;
out vec2 elemTexCoord;

// Matrices
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

// STRUCT DEFINITIONS FOR LIGHT RELATED OBJECTS

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// In from renderer
uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight pointLight;
uniform vec3 cameraPos;

vec3 computeDirectionalLight(DirectionalLight light, vec3 elemToCamera, vec3 elemNormal)
{
    vec3 lightDir = -light.direction;

    // Diffuse shading
    float diffuseFactor = max(dot(elemNormal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, elemNormal);
    float specularDot = clamp(dot(elemToCamera, reflectDir), 0, 1);
    float specularFactor = pow(specularDot, material.shininess);

    // Combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = diffuseFactor * light.diffuse * material.diffuse;
    vec3 specular = specularFactor * light.specular * material.specular;

    return (ambient + diffuse + specular);
}

vec3 computePointLight(PointLight light, vec3 elemToCamera, vec3 elemPosition, vec3 elemNormal)
{
    // Diffuse shading
    vec3 lightDir = light.position - elemPosition;
    float distance = length(lightDir);
    lightDir *= float(1) / distance;
    float diffuseFactor = max(dot(elemNormal, lightDir), 0.0);
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, elemNormal);
    float specularDot = clamp(dot(elemToCamera, reflectDir), 0, 1);
    float specularFactor = pow(specularDot, material.shininess);

    // Attenuation
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

    // Combine results    
    vec3 ambient = attenuation * light.ambient * material.ambient;
    vec3 diffuse = attenuation * diffuseFactor * light.diffuse * material.diffuse;
    vec3 specular = attenuation * specularFactor * light.specular * material.specular;

    return (ambient + diffuse + specular);
}

void main()
{
    vec3 elemPosition = vec3(modelMat * vec4(position, 1.0f));
    vec3 elemNormal = normalize(mat3(transpose(inverse(modelMat))) * normal);
    
    vec3 elemToCamera = normalize(cameraPos - elemPosition);

    vec3 tmpColor = vec3(0.0, 0.0, 0.0);

    tmpColor += computeDirectionalLight(dirLight, elemToCamera, elemNormal);
    tmpColor += computePointLight(pointLight, elemToCamera, elemPosition, elemNormal);

    elemColor = tmpColor;
    elemTexCoord = texCoord;

    gl_Position = projMat * viewMat * vec4(elemPosition, 1.0f);
}
