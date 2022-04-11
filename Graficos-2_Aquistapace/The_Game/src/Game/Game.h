#ifndef GAME_H
#define GAME_H

#include "GameBase/GameBase.h"
#include "../Objects/Player.h"

namespace Engine
{
	const int COUNT_WALLS = 4;

	class Game : public GameBase
	{
	private:
		Player* _roboBob;
		Sprite* _player;
		Sprite* _floor;
		Camera* _cameraGame;

		Cube* _walls[COUNT_WALLS];

		Cube* _box;

		const float cameraSpeed = 2.25f;
		const float cameraSpeedRot = 20;

		bool cameraType = false;

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