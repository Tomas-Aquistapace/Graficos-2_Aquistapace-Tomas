#ifndef LIGHT_H
#define LIGHT_H

#include <string>
#include "..\Export\Export.h"
#include "glm\glm\vec3.hpp"

namespace Engine
{
	enum LightType
	{
		Ambient,
		Specular,
		Directional
	};

	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
	};

	class EXPORT_API Light
	{
	private:
		Transform _transform;
		unsigned int _shader;

	public:
		Light(glm::vec3 position, glm::vec3 rotation);
		~Light();

		void SetVec3(const std::string& name, const glm::vec3& value);
		void SetVec3(const std::string& name, float x, float y, float z);
		
		void Draw();
	};
};

#endif