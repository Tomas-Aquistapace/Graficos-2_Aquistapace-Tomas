#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

namespace Engine
{
	class EXPORT_API PointLight : public Light
	{
	private:
		PointLightData _pointData;

	public:
		PointLight(Renderer* renderer, float r, float g, float b, glm::vec3 position);
		~PointLight();

		void Draw(int i) override;

		glm::vec3 GetPosition();

		void SetPosition(glm::vec3 position);
		void SetPointValues(float constant, float linear, float quadratic);
	};
};

#endif