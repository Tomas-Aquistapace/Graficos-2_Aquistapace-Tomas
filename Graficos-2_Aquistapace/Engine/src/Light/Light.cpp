#include "Light.h"
#include "GL/glew.h"

namespace Engine
{
    Light::Light(Renderer* renderer, float r, float g, float b)
    {
        _renderer = renderer;

        _data._color = { r, g, b };

        //_directionLight._diffuse = _directionLight._color * glm::vec3(0.5f);
        //_directionLight._ambient = _directionLight._diffuse * glm::vec3(0.2f);
        //_directionLight._specular = { 1.0f, 1.0f, 1.0f };

        _data._diffuse = { 0.2f, 0.2f, 0.2f };
        _data._ambient = { 0.5f, 0.5f, 0.5f };
        _data._specular = { 1.0f, 1.0f, 1.0f };

        _data._isActive = (int)true;
    }

    Light::~Light()
    {

    }

    glm::vec3 Light::GetColor()
    {
        return _data._color;
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

    void Light::SetIsActive(bool state)
    {
        _data._isActive = (int)state;
    }

    void Light::SetColor(glm::vec3 color)
    {
        _data._color = color;
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