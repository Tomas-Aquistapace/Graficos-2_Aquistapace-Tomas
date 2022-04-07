#include "Input.h"

#include "GLFW/glfw3.h"
#include <iostream>

namespace Engine
{
	static GLFWwindow* _window;
	static Camera* _camera;

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void UpdateValuesFPS();

	float _yaw = -90.f;
	float _pitch = 0.0f;
	float _lastX = 800.f / 2;
	float _lastY = 600.f / 2;

	bool _firstMouse = true;

	float _sensitivity = 1.5f;

	// ---------------------------------

	void Input::SetWindow(GLFWwindow* window)
	{
		_window = window;
	}

	bool Input::GetKey(Keycode key)
	{
		return (glfwGetKey(_window, key) == GLFW_PRESS);
	}

	bool Input::GetKeyUp(Keycode key)
	{
		return (glfwGetKey(_window, key) == GLFW_RELEASE);
	}

	void Input::SetFPSCamera(GLFWwindow* _window, Camera* camera, float sensitivity)
	{
		glfwSetCursorPosCallback(_window, mouse_callback);
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		_camera = camera;

		_sensitivity = sensitivity;
	}

	// ---------------------------------

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (_firstMouse)
		{
			_lastX = xpos;
			_lastY = ypos;
			_firstMouse = false;
		}

		float xoffset = xpos - _lastX;
		float yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top
		_lastX = xpos;
		_lastY = ypos;

		xoffset *= _sensitivity;
		yoffset *= _sensitivity;

		_yaw += xoffset;
		_pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;

		UpdateValuesFPS();
	}

	void UpdateValuesFPS()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		direction.y = sin(glm::radians(_pitch));
		direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		
		_camera->_transform.forward = glm::normalize(direction);
		_camera->_transform.right = glm::normalize(glm::cross(glm::vec3(0,1,0), _camera->_transform.forward));
		_camera->_transform.up = glm::normalize(glm::cross(_camera->_transform.forward, _camera->_transform.right));
	}
}