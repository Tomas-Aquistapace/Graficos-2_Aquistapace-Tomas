#ifndef CAMERA_H
#define CAMERA_H

#include "..\Shader\Shader.h"
#include "..\Window\Window.h"
#include "..\Entity\Entity.h"

namespace Engine
{
	enum class CameraType {
		Perspective,
		Ortho
	};

	class EXPORT_API Camera : public Entity
	{
	private:
		unsigned int _modelInd;
		unsigned int _viewInd;
		unsigned int _projectionInd;

		glm::mat4 _projection;
		glm::mat4 _view;

		// --------

		void DefaulValues();

	public:
		Camera();
		Camera(CameraType type, float widht, float height, float near, float far);
		~Camera();

		void UpdateView();
		void UpdateMVP(glm::mat4 model);
		void SetIndex(unsigned int shaderId);
		void SetCameraValues(CameraType type, float widht, float height, float near, float far);

		void LookAt(glm::vec3 target);

		// --------------------------------
		// Virtual Functions:

		void SetColor(ENTITY_COLOR color);
		void SetColor(float r, float g, float b);
		void TriggerCollision(Entity* other);
	};
}

#endif