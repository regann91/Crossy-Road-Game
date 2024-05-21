#version 330 core
out vec4 FragColor;
uniform bool useGouraudShading;

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

// In from vertex shader
in vec3 elemPosition;
in vec4 elemColor;
in vec3 elemNormal;
in vec3 vertexNormal;

// Camera position in world space
in vec3 cameraPos;


vec3 computeDirectionalLight(DirectionalLight light, vec3 normal, vec3 elemToCamera)
{
    vec3 lightDir = -light.direction;

    // Diffuse shading
    float diffuseFactor = max(dot(normal, lightDir), 0.0);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularDot = clamp(dot(elemToCamera, reflectDir), 0, 1);
    float specularFactor = pow(specularDot, material.shininess);

    // Combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = diffuseFactor * light.diffuse * material.diffuse;
    vec3 specular = specularFactor * light.specular * material.specular;

    return (ambient + diffuse + specular);
}

vec3 computePointLight(PointLight light, vec3 normal, vec3 elemToCamera)
{
    // Diffuse shading
    vec3 lightDir = light.position - elemPosition;
    float distance = length( lightDir );
    lightDir *= float(1) / distance;
    float diffuseFactor = max(dot(normal, elemToCamera), 0.0);
    
    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularDot = clamp(dot(elemToCamera, reflectDir), 0, 1);
    float specularFactor = pow(specularDot, material.shininess);

    // Attenuation
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

    // Combine results    
    vec3 ambient  = attenuation * light.ambient * material.ambient ;
    vec3 diffuse  = attenuation * diffuseFactor * light.diffuse  * material.diffuse ;
    vec3 specular = attenuation * specularFactor * light.specular * material.specular;

    return (ambient + diffuse + specular);
}

void main()
{
    // Choose the normal based on the shading model
    vec3 normal = useGouraudShading ? vertexNormal : elemNormal;

    //Surface to camera vector
    vec3 elemToCamera = normalize( cameraPos - elemPosition );

    vec3 tmpColor = vec3(0.0, 0.0, 0.0);

    tmpColor += computeDirectionalLight(dirLight, normal, elemToCamera);
    tmpColor += computePointLight(pointLight, normal, elemToCamera);

    FragColor = vec4(tmpColor,1.0);
}

