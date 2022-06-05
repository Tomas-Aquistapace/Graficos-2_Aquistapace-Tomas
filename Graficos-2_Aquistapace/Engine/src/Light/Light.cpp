#include "Light.h"
#include "GL/glew.h"

namespace Engine
{
    Light::Light(Renderer* renderer, float r, float g, float b, LightType type)
    {
        _renderer = renderer;

        _lightType = type;

        switch (_lightType)
        {
        case Engine::Directional:

            _directionLight._color = { r, g, b };

            _directionLight._direction = { 0, 0, 0 };


            //_directionLight._diffuse = _directionLight._color * glm::vec3(0.5f);
            //_directionLight._ambient = _directionLight._diffuse * glm::vec3(0.2f);
            //_directionLight._specular = { 1.0f, 1.0f, 1.0f };
            
            _directionLight._diffuse = { 0.2f, 0.2f, 0.2f };
            _directionLight._ambient = { 0.5f, 0.5f, 0.5f };
            _directionLight._specular = { 1.0f, 1.0f, 1.0f };

            _directionLight._isActive = (int)true;

            break;
        case Engine::Point:
            break;
        case Engine::SpotLight:
            break;
        }
    }

    Light::~Light()
    {

    }

    void Light::Draw()
    {
        _renderer->UpdateDirectionalLight(_directionLight);
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

    // ---------------------

    void Light::SetDirectionData(glm::vec3 direction)
    {
        _directionLight._direction = direction;
    }

    void Light::SetIsActive(bool state)
    {
        switch (_lightType)
        {
        case Engine::Directional:

            _directionLight._isActive = (int)state;

            break;
        case Engine::Point:
            break;
        case Engine::SpotLight:
            break;
        }
    }

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