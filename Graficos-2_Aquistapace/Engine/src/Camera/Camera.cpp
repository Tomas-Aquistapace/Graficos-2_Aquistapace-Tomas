#include "Camera.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"

#include <iostream>

namespace Engine
{
	Camera::Camera() : Entity()
	{
		DefaulValues();
	}

	Camera::Camera(CameraType type, float widht, float height, float near, float far) : Entity()
	{
		DefaulValues();
		SetCameraValues(type, widht, height, near, far);
	}

	Camera::~Camera()
	{

	}


	void Camera::SetFPSCamera(GLFWwindow* _window, float sensitivity)
	{
		glfwSetCursorPosCallback(_window, mouse_callback);
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		_sensitivity = sensitivity;
	}

	void Camera::UpdateView()
	{
		_view = glm::lookAt(_transform.position, _transform.position + _transform.forward, _transform.up);
	}

	void Camera::UpdateMVP(glm::mat4 model)
	{
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
		_view = glm::lookAt(_transform.position, target, _transform.up);
	}

	// --------------------------------------------
	// Internal Functions

	void Camera::DefaulValues()
	{
		//_transform.position = glm::vec3(0.0f, 0.0f, 5.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		//_cameraDirection = glm::normalize(_transform.position - cameraTarget);
		//_transform.forward = glm::vec3(0, 0, -1);
		//_transform.up = glm::vec3(0, 1, 0);

		_view = glm::lookAt(_transform.position, cameraTarget, _transform.up);
		_projection = glm::perspective(glm::radians(45.0f), 1366.0f / 768.0f, 0.1f, 100.0f);
	}

	void Camera::UpdateValues()
	{

	}

	void Camera::UpdateValuesFPS()
	{
		//_cameraFront.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		//_cameraFront.y = sin(glm::radians(_pitch));
		//_cameraFront.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		//_cameraFront = glm::normalize(_cameraFront);
		//
		//_cameraUp = glm::normalize(glm::cross(GetRight(), _cameraFront));
	}

	void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Camera* theCamera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
		
		if (theCamera->_firstMouse)
		{
			theCamera->_lastX = xpos;
			theCamera->_lastY = ypos;
			theCamera->_firstMouse = false;
		}

		float xoffset = xpos - theCamera->_lastX;
		float yoffset = theCamera->_lastY - ypos; // reversed since y-coordinates go from bottom to top
		theCamera->_lastX = xpos;
		theCamera->_lastY = ypos;

		xoffset *= theCamera->_sensitivity;
		yoffset *= theCamera->_sensitivity;

		theCamera->_yaw += xoffset;
		theCamera->_pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (theCamera->_pitch > 89.0f)
			theCamera->_pitch = 89.0f;
		if (theCamera->_pitch < -89.0f)
			theCamera->_pitch = -89.0f;

		theCamera->UpdateValuesFPS();
	}

	// ------------------------------------
	// Virtual Fuctions:

	void Camera::SetColor(ENTITY_COLOR color) { }
	void Camera::SetColor(float r, float g, float b) { }
	void Camera::TriggerCollision(Entity* other) { }
}