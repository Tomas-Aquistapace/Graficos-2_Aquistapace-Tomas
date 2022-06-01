#include "Light.h"
#include "GL/glew.h"

namespace Engine
{
    Light::Light(Renderer* renderer, glm::vec3 position, float r, float g, float b, LightType lightType)
    {
        _renderer = renderer;

        _data._position = position;
        _data._lightColor = { r, g, b };
        
        _data._diffuse = _data._lightColor * glm::vec3(0.5f);
        _data._ambient = _data._diffuse * glm::vec3(0.2f);

        _data._specular = { 1.0f, 1.0f, 1.0f };

        // Lights Types Data
        _lightType = lightType;

        _data._direction = { -0.2f, -1.0f, -0.3f };

        _data._constant = 1.0f;
        _data._linear = 0.09f;
        _data._quadratic = 0.032f;

    }

    Light::~Light()
    {

    }

    void Light::Draw()
    {
        _renderer->UpdateLight(_data, _lightType);
    }

    // -------------------

    glm::vec3 Light::GetColor()
    {
        return _data._lightColor;
    }

    glm::vec3 Light::GetPosition()
    {
        return _data._position;
    }

    glm::vec3 Light::GetDirection()
    {
        return _data._direction;
    }

    glm::vec3 Light::GetAmbient()
    {
        return _data._ambient;
    }
        
    glm::vec3 Light::GetDiffuse()
    {
        return _data._diffuse;
    }

    glm::vec3 Light::GetSpecular()
    {
        return _data._specular;
    }

    int Light::GetLightType()
    {
        return _lightType;
    }

    // --------------

    void Light::SetColor(glm::vec3 color)
    {
        //data._lightColor = color * glm::vec3(0.5f);;
        _data._diffuse = color * glm::vec3(0.5f);
        _data._ambient = _data._diffuse * glm::vec3(0.2f);
    }

    void Light::SetPosition(glm::vec3 position)
    {
        _data._position = position;
    }

    void Light::SetDirection(glm::vec3 direction)
    {
        _data._direction = direction;
    }

    void Light::SetPointLight(float constant, float linear, float quadratic)
    {
        _data._constant = constant;
        _data._linear = linear;
        _data._quadratic = quadratic;
    }

    void Light::SetAmbient(glm::vec3 ambient)
    {
        _data._ambient = ambient;
    }
    
    void Light::SetDiffuse(glm::vec3 diffuse)
    {
        _data._diffuse = diffuse;
    }
    
    void Light::SetSpecular(glm::vec3 specular)
    {
        _data._specular = specular;
    }
}