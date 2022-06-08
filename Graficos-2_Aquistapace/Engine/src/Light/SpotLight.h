#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"

namespace Engine
{
	class EXPORT_API SpotLight : public Light
	{
	private:
		SpotLightData _spotData;

	public:
		SpotLight(Renderer* renderer, float r, float g, float b, glm::vec3 position, glm::vec3 direction);
		~SpotLight();

		void Draw(int i) override;

		glm::vec3 GetPosition();
		glm::vec3 GetDirection();

		void SetPosition(glm::vec3 position);
		void SetDirection(glm::vec3 direction);
		void SetSpotValues(float constant, float linear, float quadratic);
		void SetCutOffs(float cutOff, float outerCutOff);
	};
};

#endif