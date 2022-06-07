#include "SpotLight.h"

namespace Engine
{
	SpotLight::SpotLight(Renderer* renderer, float r, float g, float b, glm::vec3 position, glm::vec3 direction) : Light(renderer, r,g,b)
	{
		_spotData._position = position;
		_spotData._direction = direction;

		_spotData._cutOff = glm::cos(glm::radians(12.5f));
		_spotData._outerCutOff = glm::cos(glm::radians(17.5f));

		_spotData._constant = 1.0f;
		_spotData._linear = 0.09f;
		_spotData._quadratic = 0.032f;
	}

	SpotLight::~SpotLight()
	{

	}

	void SpotLight::Draw()
	{
		_renderer->UpdateSpotLight(_data, _spotData);
	}

	glm::vec3 SpotLight::GetPosition()
	{
		return _spotData._position;
	}

	glm::vec3 SpotLight::GetDirection()
	{
		return _spotData._direction;
	}

	void SpotLight::SetPosition(glm::vec3 position)
	{
		_spotData._position = position;
	}

	void SpotLight::SetDirection(glm::vec3 direction)
	{
		_spotData._direction = direction;
	}

	void SpotLight::SetSpotValues(float constant, float linear, float quadratic)
	{
		_spotData._constant = constant;
		_spotData._linear = linear;
		_spotData._quadratic = quadratic;
	}

	void SpotLight::SetCutOffs(float cutOff, float outerCutOff)
	{
		_spotData._cutOff = glm::cos(glm::radians(cutOff));
		_spotData._outerCutOff = glm::cos(glm::radians(outerCutOff));
	}
}