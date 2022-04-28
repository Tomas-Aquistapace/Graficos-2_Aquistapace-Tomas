#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include "..\Renderer\Renderer.h"
#include "..\Export\Export.h"
#include "glm\glm\vec3.hpp"

namespace Engine
{
	enum LightType
	{
		Directional,
		Point,
		SpotLight
	};

	class EXPORT_API Light
	{
	private:		
		// LightData existe en el Renderer para evitar una referencia cruzada al hacer las llamadas
		LightData data;
		Renderer* _renderer;

	public:
		Light(Renderer* renderer, glm::vec3 position, float r, float g, float b);
		~Light();
		
		void Draw();

		glm::vec3 GetColor();
		glm::vec3 GetPosition();
		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();

		void SetColor(glm::vec3 color);
		void SetPosition(glm::vec3 position);
		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);
	};
};

#endif