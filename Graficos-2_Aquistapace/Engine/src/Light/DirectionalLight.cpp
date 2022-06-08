#include "DirectionalLight.h"

namespace Engine
{
	DirectionalLight::DirectionalLight(Renderer* renderer, float r, float g, float b, glm::vec3 direction) : Light(renderer, r,g,b)
	{
		_directionData._direction = direction;
	}

	DirectionalLight::~DirectionalLight()
	{

	}

	void DirectionalLight::Draw(int i)
	{
		_renderer->UpdateDirectionalLight(_data, _directionData);
	}

	glm::vec3 DirectionalLight::GetDirection()
	{
		return _directionData._direction;
	}

	void DirectionalLight::SetDirection(glm::vec3 direction)
	{
		_directionData._direction = direction;
	}
}