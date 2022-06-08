#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <vector>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

using namespace std;

namespace Engine
{
	const int MAX_INDIVIDUALS_LIGHTS = 4;

	class EXPORT_API LightManager
	{
	private:
		DirectionalLight* _directional;
		vector<PointLight*> _pointsList;
		vector<SpotLight*> _spotsList;

	public:
		LightManager();
		~LightManager();

		void AddNewDirectional(Renderer* renderer, float r, float g, float b, glm::vec3 direction);
		void AddNewPoint(Renderer* renderer, float r, float g, float b, glm::vec3 position);
		void AddNewSpot(Renderer* renderer, float r, float g, float b, glm::vec3 position, glm::vec3 direction);

		void RemoveDirectional();
		void RemovePoint(int i);
		void RemoveSpot(int i);

		DirectionalLight* GetDirectional();
		PointLight* GetPoint(int i);
		SpotLight* GetSpot(int i);

		void DrawLights();
	};
};

#endif