#ifndef GAME_H
#define GAME_H

#include "GameBase/GameBase.h"
#include "../Objects/Player.h"

namespace Engine
{
	class Game : public GameBase
	{
	private:
		Player* _roboBob;
		Sprite* _wall1;
		Sprite* _wall2;
		Sprite* _box;
		Camera* _cameraGame;

		const float cameraSpeed = 2.25f;
		const float cameraSpeedRot = 20;

	public:
		Game();
		~Game();

		void Start();
		void Play();
		void Update(float deltaTime) override;
		void End();
	};
}

#endif;