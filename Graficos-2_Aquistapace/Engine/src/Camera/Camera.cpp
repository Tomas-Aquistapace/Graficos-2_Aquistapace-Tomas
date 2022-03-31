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

	void Camera::UpdateView()
	{
		_view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
	}

	void Camera::UpdateMVP(glm::mat4 model)
	{
		//UpdateView();
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
	}


	void Camera::LookAt(glm::vec3 target)
	{
		_view = glm::lookAt(_cameraPos, target, _cameraUp);
	}
	

	void Camera::SetPosition(float x, float y, float z)
	{
		_cameraPos = glm::vec3(x,y,z);
		UpdateView();
	}
	void Camera::SetPosition(glm::vec3 position)
	{
		_cameraPos = position;
		UpdateView();
	}

	void Camera::SetDirection(float x, float y, float z)
	{
		_cameraDirection = glm::normalize(_cameraPos - glm::vec3(x,y,z));
		UpdateView();
	}
	void Camera::SetDirection(glm::vec3 target)
	{
		_cameraDirection = glm::normalize(_cameraPos - target);
		UpdateView();
	}

	void Camera::MoveCamera(float speed, glm::vec3 direction)
	{
		SetPosition(_cameraPos += speed * direction);
	}

	void Camera::RotateCamera()
	{

	}

	glm::vec3 Camera::GetPosition()
	{
		return _cameraPos;
	}
	
	glm::vec3 Camera::GetFront()
	{
		return _cameraFront;
	}

	glm::vec3 Camera::GetDirection()
	{
		return _cameraDirection;
	}

	// --------------------------------------------
	// Internal Functions

	void Camera::DefaulValues()
	{
		_cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		//_cameraDirection = glm::normalize(_cameraPos - cameraTarget);
		//_cameraFront = glm::normalize(glm::cross(up, _cameraDirection));
		//_cameraUp = glm::cross(_cameraDirection, _cameraFront);
		
		_cameraDirection = glm::normalize(_cameraPos - cameraTarget);
		_cameraFront = glm::vec3(0, 0, -1);
		_cameraUp = glm::vec3(0, 1, 0);

		_view = glm::lookAt(_cameraPos, cameraTarget, up);
		_projection = glm::perspective(glm::radians(45.0f), 1366.0f / 768.0f, 0.1f, 100.0f);
	}
}