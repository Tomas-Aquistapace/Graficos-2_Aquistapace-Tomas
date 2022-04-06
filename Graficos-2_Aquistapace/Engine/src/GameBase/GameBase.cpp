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
	}

	GameBase::~GameBase()
	{
		if (_window != NULL)
			delete _window;
		if (_renderer != NULL)
			delete _renderer;
		if (_collisionManager != NULL)
			delete _collisionManager;
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
		_renderer->UnlockCamera();
		_renderer->StopShader();
		glfwTerminate();
	}

	//===========================================

	void GameBase::SetCameraInUse(Camera* camera)
	{
		_renderer->SetCameraInUse(camera);
	}

	void GameBase::SetFPSCamera(Camera* camera, float sensitivity)
	{
		camera->SetFPSCamera(_window->ReturnWindow(), sensitivity);
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