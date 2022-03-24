#ifndef GAME_BASE_H
#define GAME_BASE_H

#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../Camera/Camera.h"
#include "../Shape/Shape.h"
#include "../Sprite/Sprite.h"
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

		std::vector<Camera*> _cameras; // que lo haga el usuario si quiere
		Camera* _defaultCamera;

	public:
		GameBase();
		~GameBase();

		int StartEngine(int width, int height, const char* windowName);
		void UpdateEngine(float r, float g, float b, float a);
		void EndEngine();

		virtual void Update(float deltatime) = 0;

		//void SetCamera(CameraType type, float width, float height, float near, float far);
		//void SetCameraPosition(float x, float y, float z);


		void CreateCamera(CameraType type, float width, float height, float near, float far);
		void SelectCamera(int i);

		Camera* GetCamera(int i);
		Renderer* GetRenderer();
		CollisionManager* GetCollisionManager();
	};
}

#endif;