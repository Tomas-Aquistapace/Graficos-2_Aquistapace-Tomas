#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include "..\Renderer\Renderer.h"
#include "..\Export\Export.h"
#include "glm\glm\vec3.hpp"

namespace Engine
{
	class EXPORT_API Light
	{
	protected:
		LightData _data;
		Renderer* _renderer;

	public:
		Light(Renderer* renderer, float r, float g, float b);
		~Light();
		
		virtual void Draw() = 0;

		glm::vec3 GetColor();
		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();

		void SetIsActive(bool state);

		void SetColor(glm::vec3 color);
		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);
	};
};

#endif