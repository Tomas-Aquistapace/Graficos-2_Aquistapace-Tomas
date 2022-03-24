#include "GameBase.h"
#include <iostream>
#include <time.h>
#include "GLFW/glfw3.h"
#include "../Input/Input.h"

namespace Engine
{
	float deltaTime;

	GameBase::GameBase()
	{
		srand(time(0));
		_window = new Window();
		_renderer = new Renderer();
		_collisionManager = new CollisionManager();

		_defaultCamera = new Camera();

		_renderer->SetCameraInUse(_defaultCamera);
	}

	GameBase::~GameBase()
	{
		if (_window != NULL)
			delete _window;
		if (_renderer != NULL)
			delete _renderer;
		if (_collisionManager != NULL)
			delete _collisionManager;

		if(!_cameras.empty())
		{
			for(Camera* obj : _cameras)
			{
				if (obj != NULL)
					delete obj;
			}
			_cameras.clear();
		}
	}

	int GameBase::StartEngine(int width, int height, const char* windowName) 
	{
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_window->CreateWindow(width, height, windowName, NULL);
		_window->InitWindow();

		Input::SetWindow(_window->ReturnWindow());

		_renderer->InitGlew();
		_renderer->CreateShader();
	}

	void GameBase::UpdateEngine(float r, float g, float b, float a)
	{
		while (!_window->WindowShouldClose())
		{
			/* Render here */
			_window->ClearWindow(r, g, b, a);
			Time::DeltaTime(deltaTime);
			Update(deltaTime); // --> Aca se utiliza un metodo virtual para poder dibujar los objetos del Game.cpp

			/* Swap front and back buffers */
			_window->SwapBuffers();

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	
	void GameBase::EndEngine()
	{
		_renderer->StopShader();
		glfwTerminate();
	}

	//===========================================

	//void GameBase::SetCamera(CameraType type, float widht, float height, float near, float far)
	//{
	//	_renderer->SetCameraValues(type, widht, height, near, far);
	//}
	//
	//void GameBase::SetCameraPosition(float x, float y, float z)
	//{
	//	_renderer->SetCameraPosition(x, y, z);
	//}





	void GameBase::CreateCamera(CameraType type, float width, float height, float near, float far)
	{
		Camera* newCamera = new Camera();
		newCamera->SetCameraValues(type, width, height, near, far);
		_cameras.push_back(newCamera);
	}

	void GameBase::SelectCamera(int i)
	{
		_renderer->SetCameraInUse(GetCamera(i));
	}



	Camera* GameBase::GetCamera(int i)
	{
		if (!_cameras.empty())
		{
			for (int j = 0; j < _cameras.size(); j++)
			{
				if (j == i)
					return _cameras[i];
			}
			std::cout << "ERROR::the value not exist in the vector" << std::endl;
		}
		else
			std::cout << "ERROR::the vector is empty" << std::endl;

		return _defaultCamera;
	}

	Renderer* GameBase::GetRenderer()
	{
		return _renderer;
	}

	CollisionManager* GameBase::GetCollisionManager()
	{
		return _collisionManager;
	}
}