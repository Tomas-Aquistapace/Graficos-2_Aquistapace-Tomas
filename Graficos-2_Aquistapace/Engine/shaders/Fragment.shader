#version 330 core

out vec4 FragColor;

struct Material 
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Directional
{
    vec3 direction;
};

struct PointLight
{
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    float algo;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;

uniform Material material;

uniform Light light;
uniform Directional directional;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform int lightType;

vec3 CalculateDirectionalLight(Material _material, Light _light, Directional _directional, vec2 _texCoords, vec3 _normal);
vec3 CalculatePointLight(Material _material, Light _light, PointLight _pointLight, vec2 _texCoords, vec3 _normal);

void main()
{
    if (lightType == 0) // Directional
    {
        //// ambient
        //vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
        //
        //// diffuse 
        //vec3 norm = normalize(Normal);
        //vec3 lightDir = normalize(-directional.direction);
        //float diff = max(dot(norm, lightDir), 0.0);
        //vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
        //
        //// specular
        //vec3 viewDir = normalize(viewPos - FragPos);
        //vec3 reflectDir = reflect(-lightDir, norm);
        //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        //vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
        //
        //vec3 result = ambient + diffuse + specular;
        //FragColor = vec4(result, 1.0);

        // ---------- \\

        vec3 directionalResult = CalculateDirectionalLight(material, light, directional, TexCoords, Normal);
        
        FragColor = vec4(directionalResult, 1.0);
    }
    else if(lightType == 1) // Point
    {
        //// ambient
        //vec3 ambient = light.ambient * texture(material.diffuse, TexCoords);
        //
        //// diffuse 
        //vec3 norm = normalize(Normal);
        //vec3 lightDir = normalize(light.position - FragPos);
        //float diff = max(dot(norm, lightDir), 0.0);
        //vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords);
        //
        //// specular
        //vec3 viewDir = normalize(viewPos - FragPos);
        //vec3 reflectDir = reflect(-lightDir, norm);
        //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        //vec3 specular = light.specular * spec * texture(material.specular, TexCoords);
        //
        //// attenuation
        //float distance = length(light.position - FragPos);
        //float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
        //
        //ambient *= attenuation;
        //diffuse *= attenuation;
        //specular *= attenuation;
        //
        //vec3 result = ambient + diffuse + specular;
        //FragColor = vec4(result, 1.0);

        // ---------- \\

        vec3 pointResult = CalculatePointLight(material, light, pointLight, TexCoords, Normal);

        FragColor = vec4(pointResult, 1.0);
    }
    else if(lightType == 2) // SpotLight
    {





    }
}

vec3 CalculateDirectionalLight(Material _material, Light _light, Directional _directional, vec2 _texCoords, vec3 _normal)
{
    // ambient
    vec3 ambient = _light.ambient * vec3(texture(_material.diffuse, _texCoords));

    // diffuse 
    vec3 norm = normalize(_normal);
    vec3 lightDir = normalize(-_directional.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diff * vec3(texture(_material.diffuse, _texCoords));

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _material.shininess);
    vec3 specular = _light.specular * spec * vec3(texture(_material.specular, _texCoords));

    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(Material _material, Light _light, PointLight _pointLight, vec2 _texCoords, vec3 _normal)
{
    // ambient
    vec3 ambient = _light.ambient * texture(_material.diffuse, _texCoords);

    // diffuse 
    vec3 norm = normalize(_normal);
    vec3 lightDir = normalize(_light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diff * texture(_material.diffuse, _texCoords);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _material.shininess);
    vec3 specular = _light.specular * spec * texture(_material.specular, _texCoords);

    // attenuation
    float distance = length(_light.position - FragPos);
    float attenuation = 1.0 / (_pointLight.constant + _pointLight._linear * distance + _pointLight.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}