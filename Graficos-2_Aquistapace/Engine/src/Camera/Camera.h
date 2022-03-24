#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "glm\glm\mat4x4.hpp"
#include "..\Shader\Shader.h"
#include "..\Export\Export.h"

namespace Engine
{
	enum class CameraType {
		Perspective,
		Ortho
	};

	class EXPORT_API Camera
	{
	private:
		unsigned int _modelInd;
		unsigned int _viewInd;
		unsigned int _projectionInd;

		glm::mat4 _projection;
		glm::mat4 _view;

		glm::vec3 _cameraPos;
		glm::vec3 _cameraDirection;
		glm::vec3 _cameraRight;
		glm::vec3 _cameraUp;

	public:
		Camera();
		~Camera();

		//void UpdateCameraVectors();
		void UpdateView();
		void UpdateMVP(glm::mat4 model);
		void SetIndex(unsigned int shaderId);
		void SetCameraValues(CameraType type, float widht, float height, float near, float far);

		void SetCameraPosition(float x, float y, float z);
		void SetCameraDirection(glm::vec3 target);
		
		void LookAt(glm::vec3 target);
	};
}

#endif