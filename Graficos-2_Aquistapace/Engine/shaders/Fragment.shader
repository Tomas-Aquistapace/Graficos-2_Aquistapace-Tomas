#version 330 core

out vec4 FragColor;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirectionLight
{
    vec3 color;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    int isActive;
};

struct PointLight
{
    vec3 color;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    int isActive;
};

in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec4 u_color;

uniform vec3 u_viewPos;
uniform DirectionLight u_directionLight;
uniform PointLight u_pointLight;
uniform Material u_material;

vec4 CalculateDirectionData(vec3 normal, vec3 viewDirection);
vec4 CalculatePointLight(vec3 normal, vec3 viewDirection);

void main()
{
    vec4 resultColor = u_color;
    vec3 normal = normalize(Normal);
    vec3 viewDirection = normalize(u_viewPos - FragPos);

    if (u_directionLight.isActive != 0)
    {
        resultColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

        resultColor += CalculateDirectionData(normal, viewDirection);
    }
    
    if (u_pointLight.isActive != 0)
    {
        resultColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

        resultColor += CalculatePointLight(normal, viewDirection);
    }
    
    FragColor = resultColor;
}

vec4 CalculateDirectionData(vec3 normal, vec3 viewDirection)
{
    // ambient
    vec3 ambient = u_directionLight.ambient * vec3(texture(u_material.diffuse, TexCoords));

    // diffuse
    vec3 lightDir = normalize(-u_directionLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = u_directionLight.diffuse * diff * vec3(texture(u_material.diffuse, TexCoords));

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_directionLight.specular * spec * vec3(texture(u_material.specular, TexCoords));

    return vec4((ambient + diffuse + specular), 1.0f);
}

vec4 CalculatePointLight(vec3 normal, vec3 viewDirection)
{
    // ambient
    vec3 ambient = u_pointLight.ambient * vec3(texture(u_material.diffuse, TexCoords));

    // diffuse 
    //vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_pointLight.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = u_pointLight.diffuse * diff * vec3(texture(u_material.diffuse, TexCoords));

    // specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_pointLight.specular * spec * vec3(texture(u_material.specular, TexCoords));

    // attenuation
    float distance = length(u_pointLight.position - FragPos);
    float attenuation = 1.0 / (u_pointLight.constant + u_pointLight.linear * distance + u_pointLight.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return vec4((ambient + diffuse + specular), 1.0f);
}