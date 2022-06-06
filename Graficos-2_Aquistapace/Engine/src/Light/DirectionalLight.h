#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

namespace Engine
{
	class EXPORT_API DirectionalLight : public Light
	{
	private:
		DirectionLightData _directionData;

	public:
		DirectionalLight(Renderer* renderer, float r, float g, float b, glm::vec3 direction);
		~DirectionalLight();

		void Draw() override;

		glm::vec3 GetDirection();

		void SetDirection(glm::vec3 direction);
	};
};

#endif