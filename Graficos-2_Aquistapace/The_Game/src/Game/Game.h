#ifndef GAME_H
#define GAME_H

#include "GameBase/GameBase.h"
#include "../Objects/Player.h"

namespace Engine
{
	class Game : public GameBase
	{
	private:
		Player* _bob;
		Sprite* _wall1;
		Sprite* _wall2;
		Sprite* _box;

		Player* _roboBob;

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