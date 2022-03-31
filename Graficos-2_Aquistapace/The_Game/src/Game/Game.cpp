#include "Game.h"
#include <iostream>
#include <time.h>

namespace Engine
{
	Game::Game(): GameBase()
	{
		_roboBob = NULL;
		_wall1 = NULL;
		_wall2 = NULL;
		_box = NULL;

		_cameraGame = NULL;
	}

	Game::~Game()
	{
		if (_roboBob != NULL)
		{
			delete _roboBob;
			_roboBob = NULL;
		}
		if (_wall1 != NULL)
		{
			delete _wall1;
			_wall1 = NULL;
		}
		if (_wall2 != NULL)
		{
			delete _wall2;
			_wall2 = NULL;
		}
		if (_box != NULL)
		{
			delete _box;
			_box = NULL;
		}

		if (_cameraGame != NULL)
		{
			delete _cameraGame;
			_cameraGame = NULL;
		}
	}

	void Game::Start()
	{
		StartEngine(1200, 600, "Graficos 2 - Aquistapace");
		srand(time(NULL));

		_cameraGame = new Camera(CameraType::Perspective, 1366.0f, 768.0f, 0.1f, 100.0f);
		_cameraGame->SetPosition(0,0,5);

		SetCameraInUse(_cameraGame);

		// --------------------------------
		
		_wall1 = new Sprite(GetRenderer());
		_wall1->InitTexture();
		_wall1->ImportTexture("res/wall.jpg");
		_wall1->SetPosition(0, 1.2, 0);
		_wall1->SetStaticState(true);
		GetCollisionManager()->AddNewObject(_wall1);
		
		// --------------------------------

		_wall2 = new Sprite(GetRenderer());
		_wall2->InitTexture();
		_wall2->ImportTexture("res/wall.jpg");
		_wall2->SetPosition(0, -1.2, 0);
		_wall2->SetStaticState(true);
		GetCollisionManager()->AddNewObject(_wall2);
		
		// --------------------------------
		
		_box = new Sprite(GetRenderer());
		_box->InitTexture();
		_box->ImportTexture("res/crate1_diffuse.png");
		_box->SetPosition(0, 0, 0);
		GetCollisionManager()->AddNewObject(_box);

		// --------------------------------

		_roboBob = new Player(GetRenderer(), ivec2(9,5), 2);
		_roboBob->GetAnimation()->AddFrame(0.1, 0, 7);

		_roboBob->InitTexture();
		_roboBob->ImportTexture("res/character_robot_sheet.png");
		_roboBob->SetPosition(-1.8, 0, 0);
		GetCollisionManager()->AddNewObject(_roboBob);
	}
	
	void Game::Play()
	{
		UpdateEngine(0.0f, 0.0f, 0.0f, 1);
	}

	void Game::Update(float deltaTime)
	{
		_roboBob->Move(deltaTime);

		GetCollisionManager()->CheckAllCollisions();

		if (Input::GetKey(Keycode::I))
		{
			_cameraGame->MoveCamera(cameraSpeed * deltaTime, _cameraGame->GetFront());
		}
		if (Input::GetKey(Keycode::K))
		{
			_cameraGame->MoveCamera(-cameraSpeed * deltaTime, _cameraGame->GetFront());
		}
		if (Input::GetKey(Keycode::J))
		{
		}
		if (Input::GetKey(Keycode::L))
		{
		}

		_wall1->Draw();
		_wall2->Draw();
		_box->Draw();
	}

	void Game::End()
	{
		EndEngine();
	}
}