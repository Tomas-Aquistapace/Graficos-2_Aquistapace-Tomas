#include "Camera.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"

namespace Engine
{
	Camera::Camera()
	{
		_projection = glm::mat4(1.0f);
		_view = glm::mat4(1.0f);

		_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
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
		_view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
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

	void Camera::SetCameraValues(CameraType type, float near, float far)
	{
		switch (type)
		{
		case CameraType::Perspective:
			_projection = glm::perspective(glm::radians(45.0f), 1366.0f / 768.0f, near, far);
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

}