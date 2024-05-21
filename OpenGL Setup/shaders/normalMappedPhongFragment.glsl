#version 330 core
out vec4 FragColor;

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

uniform sampler2D tex;
uniform sampler2D normals;

// In from vertex shader
in vec3 elemPosition;
in vec4 elemColor;
in vec3 elemNormal;
in vec2 elemTexCoord;

// Camera position in world space
in vec3 cameraPos;

const float normalWeight = 1;

vec3 computeDirectionalLight(DirectionalLight light, vec3 elemToCamera, vec3 normal)
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

vec3 computePointLight(PointLight light, vec3 elemToCamera, vec3 normal)
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


// FUNCTIONS TO CALCULATE NEW NORMAL
vec4 angleDot(float dotprod, vec3 axis)
{
    float s = sqrt(0.5 - 0.5 * dotprod);
    float w = sqrt(0.5 + 0.5 * dotprod);
    return vec4(axis * s, w);
}

vec4 two_dirs_to_quat(vec3 v1, vec3 v2){
    vec3 axis = cross(v1, v2);
    float dotprod = dot(v1, v2);
    return angleDot(dotprod, axis);
}

vec4 quatMultiplication(vec4 quat1, vec4 quat2) {
	return vec4(
		quat2.xyz * quat1.w + quat1.xyz * quat2.w + cross(quat1.xyz, quat2.xyz),
		quat1.w * quat2.w - dot(quat1.xyz, quat2.xyz)
	);
}

vec3 rotate(vec4 quat, vec3 vec) {
    vec4 quatConj = quat * vec4(-1, -1, -1, 1);
	return quatMultiplication(quat, quatMultiplication(vec4(vec, 0), quatConj)).xyz;
}


void main()
{
    //Surface to camera vector
    vec3 elemToCamera = normalize( cameraPos - elemPosition );

    vec3 tmpColor = vec3(0.0, 0.0, 0.0);

    vec3 normal = texture(normals, elemTexCoord).xyz;

    // Calculate normal from normal map
    normal = normal - vec3(0.5,0.5, 0);
    normal.xy = normalWeight * normal.xy;
    normal = normalize(normal);

    // Align modified normal on elem normal using quaternion
    vec4 quaternion = two_dirs_to_quat(vec3(0,0,1), elemNormal);
    vec3 newNormal = rotate(quaternion, normal);

    tmpColor += computeDirectionalLight(dirLight, elemToCamera, newNormal);
    tmpColor += computePointLight(pointLight, elemToCamera, newNormal);

    FragColor = vec4(tmpColor,1.0);
    //FragColor = texture(normals, elemTexCoord);
}

