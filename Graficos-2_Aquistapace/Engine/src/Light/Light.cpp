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
        return data._lightColor;
    }

    glm::vec3 Light::GetPosition()
    {
        return data._position;
    }

    glm::vec3 Light::GetAmbient()
    {
        return data._ambient;
    }
        
    glm::vec3 Light::GetDiffuse()
    {
        return data._diffuse;
    }

    glm::vec3 Light::GetSpecular()
    {
        return data._specular;
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
        data._diffuse = color * glm::vec3(0.5f);
        data._ambient = data._diffuse * glm::vec3(0.2f);
    }

    void Light::SetPosition(glm::vec3 position)
    {
        data._position = position;
    }

    void Light::SetAmbient(glm::vec3 ambient)
    {
        data._ambient = ambient;
    }
    
    void Light::SetDiffuse(glm::vec3 diffuse)
    {
        data._diffuse = diffuse;
    }
    
    void Light::SetSpecular(glm::vec3 specular)
    {
        data._specular = specular;
    }
}