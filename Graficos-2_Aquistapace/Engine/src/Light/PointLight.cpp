#include "PointLight.h"

namespace Engine
{
	PointLight::PointLight(Renderer* renderer, float r, float g, float b, glm::vec3 position) : Light(renderer, r,g,b)
	{
		_pointData._position = position;

		_pointData._constant = 1.0f;
		_pointData._linear = 0.09f;
		_pointData._quadratic = 0.032f;
	}

	PointLight::~PointLight()
	{

	}

	void PointLight::Draw(int i)
	{
		_renderer->UpdatePointLight(_data, _pointData, i);
	}

	glm::vec3 PointLight::GetPosition() 
	{
		return _pointData._position;
	}

	void PointLight::SetPosition(glm::vec3 position)
	{
		_pointData._position = position;
	}

	void PointLight::SetPointValues(float constant, float linear, float quadratic)
	{
		_pointData._constant = constant;
		_pointData._linear = linear;
		_pointData._quadratic = quadratic;
	}
}