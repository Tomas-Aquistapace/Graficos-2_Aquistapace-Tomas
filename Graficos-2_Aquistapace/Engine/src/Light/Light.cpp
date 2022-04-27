#include "Light.h"
#include "GL/glew.h"

namespace Engine
{
    Light::Light(Renderer* renderer, glm::vec3 position, float r, float g, float b)
    {
        _renderer = renderer;

        data._position = position;
        data._lightColor = { r, g, b };
        
        data._diffuse = data._lightColor * glm::vec3(0.5f);
        data._ambient = data._diffuse * glm::vec3(0.2f);

        data._specular = { 1.0f, 1.0f, 1.0f };
    }

    Light::~Light()
    {

    }

    void Light::Draw()
    {
        _renderer->UpdateLight(data);
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

    void Light::SetColor(glm::vec3 color)
    {
        data._lightColor = color;
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