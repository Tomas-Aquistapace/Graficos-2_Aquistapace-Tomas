#ifndef GAME_BASE_H
#define GAME_BASE_H

#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../Camera/Camera.h"
#include "../Light/Light.h"
#include "../Shape/Shape.h"
#include "../Sprite/Sprite.h"
#include "../Models/Cube/Cube.h"
#include "../Animation/Animation.h"
#include "../Input/Input.h"
#include "../Time/Time.h"
#include "../CollisionManager/CollisionManager.h"
#include "glm/glm/glm.hpp"

namespace Engine
{
	class EXPORT_API GameBase
	{
		Renderer* _renderer;
		Window* _window;
		CollisionManager* _collisionManager;

	public:
		GameBase();
		~GameBase();

		int StartEngine(int width, int height, const char* windowName);
		void UpdateEngine(float r, float g, float b, float a);
		void EndEngine();

		virtual void Update(float deltatime) = 0;

		void SetCameraInUse(Camera* camera);
		void ActivateFPSCamera(Camera* camera, float sensitivity);
		void DeactivateFPSCamera();

		Renderer* GetRenderer();
		CollisionManager* GetCollisionManager();
	};
}

#endif;