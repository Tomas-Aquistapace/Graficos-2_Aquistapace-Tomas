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

		// Mouse:
		float _yaw = -90.f;
		float _pitch = 0.0f;
		float _lastX = 800.f / 2;
		float _lastY = 600.f / 2;

		bool _firstMouse = true;

		float _sensitivity = 1.5f;
		// --------

		void DefaulValues();
		void UpdateValues();
		void UpdateValuesFPS();
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	public:
		Camera();
		Camera(CameraType type, float widht, float height, float near, float far);
		~Camera();

		void SetFPSCamera(GLFWwindow* _window, float sensitivity);
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