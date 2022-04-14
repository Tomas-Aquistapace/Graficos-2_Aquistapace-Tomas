#include "Light.h"
#include "GL/glew.h"

namespace Engine
{
    Light::Light(unsigned int shader, glm::vec3 position, glm::vec3 rotation)
    {
        _shader = shader;

        _transform.position = position;
        _transform.rotation = rotation;
    }

    Light::~Light()
    {

    }

    void Light::SetVec3(const std::string& name, const glm::vec3& value)
    {
        glUniform3fv(glGetUniformLocation(_shader, name.c_str()), 1, &value[0]);
    }

    void Light::SetVec3(const std::string& name, float x, float y, float z)
    {
        glUniform3f(glGetUniformLocation(_shader, name.c_str()), x, y, z);
    }

    void Light::Draw()
    {
        //lightingShader.use();
        //SetVec3(ID, "objectColor", 1.0f, 0.5f, 0.31f);
        SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
        SetVec3("lightPos", _transform.position);
        //lightingShader.setVec3("viewPos", camera.Position);
    }
}