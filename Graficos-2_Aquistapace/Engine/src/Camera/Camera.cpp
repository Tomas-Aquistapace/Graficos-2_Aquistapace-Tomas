#include "Camera.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"

namespace Engine
{
	Camera::Camera()
	{
		DefaulValues();
	}
	
	Camera::Camera(CameraType type, float widht, float height, float near, float far)
	{
		DefaulValues();
		SetCameraValues(type, widht, height, near, far);
	}

	Camera::~Camera()
	{

	}

	//void Camera::UpdateCameraVectors()
	//{
	//	  glm::vec3 front;
	//	  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	  front.y = sin(glm::radians(pitch));
	//	  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	  cameraFront = glm::normalize(front);
	//	  right = glm::normalize(glm::cross(cameraFront, cameraUp));
	//	  up = glm::normalize(glm::cross(right, cameraFront));
	//}

	void Camera::UpdateView()
	{
		_view = glm::lookAt(_cameraPos, _cameraPos + _cameraRight, _cameraUp);
	}

	void Camera::UpdateMVP(glm::mat4 model)
	{
		UpdateView();
		glUniformMatrix4fv(_modelInd, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(_viewInd, 1, GL_FALSE, glm::value_ptr(_view));
		glUniformMatrix4fv(_projectionInd, 1, GL_FALSE, glm::value_ptr(_projection));
	}

	void Camera::SetIndex(unsigned int shaderId)
	{
		_modelInd = glGetUniformLocation(shaderId, "model");
		_viewInd = glGetUniformLocation(shaderId, "view");
		_projectionInd = glGetUniformLocation(shaderId, "projection");
	}

	void Camera::SetCameraValues(CameraType type, float widht, float height, float near, float far)
	{
		switch (type)
		{
		case CameraType::Perspective:
			_projection = glm::perspective(glm::radians(45.0f), widht / height, near, far);
			break;

		case CameraType::Ortho:
			_projection = glm::ortho(-1.5f, 1.5f, -1.0f, 1.0f, near, far);
			break;
		}
		_view = glm::mat4(1.0f);
	}

	void Camera::SetCameraPosition(float x, float y, float z)
	{
		_cameraPos = glm::vec3(x, y, z);
	}

	void Camera::SetCameraDirection(glm::vec3 target)
	{
		_cameraDirection = glm::normalize(_cameraPos - target);
	}

	void Camera::LookAt(glm::vec3 target)
	{
		_view = glm::lookAt(_cameraPos, target, _cameraUp);
	}

	// --------------------------------------------
	// Internal Functions

	void Camera::DefaulValues()
	{
		_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		_cameraDirection = glm::normalize(_cameraPos - cameraTarget);

		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		_cameraRight = glm::normalize(glm::cross(up, _cameraDirection));

		_cameraUp = glm::cross(_cameraDirection, _cameraRight);


		_view = glm::lookAt(_cameraPos, cameraTarget, up);

		_projection = glm::perspective(glm::radians(45.0f), 1366.0f / 768.0f, 0.1f, 100.0f);
	}
}