#include "Game.h"
#include <iostream>
#include <time.h>

namespace Engine
{
	Game::Game(): GameBase()
	{
		_roboBob = NULL;
		_wall1 = NULL;
		_floor = NULL;
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
		if (_floor != NULL)
		{
			delete _floor;
			_floor = NULL;
		}
		if (_box != NULL)
		{
			delete _box;
			_box = NULL;
		}
		if (_player != NULL)
		{
			delete _player;
			_player = NULL;
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
		_cameraGame->SetRotationY(180);

		SetCameraInUse(_cameraGame);
		SetFPSCamera(_cameraGame, 0.05f);

		// --------------------------------
		
		_wall1 = new Sprite(GetRenderer());
		_wall1->InitTexture();
		_wall1->ImportTexture("res/wall.jpg");
		_wall1->SetPosition(0, 1.2, 0);
		_wall1->SetStaticState(true);
		GetCollisionManager()->AddNewObject(_wall1);
		
		// --------------------------------

		_floor = new Sprite(GetRenderer());
		_floor->InitTexture();
		_floor->ImportTexture("res/camouflage.png");
		_floor->SetPosition(0, -1.2, 0);
		_floor->SetRotationX(90);
		_floor->SetScale(glm::vec3(10,10,10));
		_floor->SetStaticState(true);
		GetCollisionManager()->AddNewObject(_floor);
		
		// --------------------------------
		
		_box = new Sprite(GetRenderer());
		_box->InitTexture();
		_box->ImportTexture("res/crate1_diffuse.png");
		_box->SetPosition(0, 0, 0);
		GetCollisionManager()->AddNewObject(_box);

		// --------------------------------

		_player = new Sprite(GetRenderer());
		_player->InitTexture();
		_player->ImportTexture("res/BOB-ESPONJA-1-22.png");
		_player->SetPosition(0, 0, 5);
		//GetCollisionManager()->AddNewObject(_player);

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
		UpdateEngine(0.2f, 0.2f, 0.2f, 1);
	}

	void Game::Update(float deltaTime)
	{
		//_roboBob->Move(deltaTime);

		if (Input::GetKey(Keycode::W))
		{
			_player->SetPosition(_player->_transform.position - (_player->_transform.forward * (cameraSpeed * deltaTime)));
		}
		else if (Input::GetKey(Keycode::S))
		{
			_player->SetPosition(_player->_transform.position + (_player->_transform.forward * (cameraSpeed * deltaTime)));
		}
		if (Input::GetKey(Keycode::A))
		{
			_player->SetPosition(_player->_transform.position - (_player->_transform.right * (cameraSpeed * deltaTime)));
		}
		else if (Input::GetKey(Keycode::D))
		{
			_player->SetPosition(_player->_transform.position + (_player->_transform.right * (cameraSpeed * deltaTime)));
		}

		if (Input::GetKey(Keycode::SPACE))
			cameraType = !cameraType;

		if(!cameraType)
			_cameraGame->FirstPerson(_player->_transform);
		else
			_cameraGame->ThirdPerson(_player->_transform, glm::vec3(0,1,1));
		
		_cameraGame->UpdateView();

		GetCollisionManager()->CheckAllCollisions();

		_wall1->Draw();
		_floor->Draw();
		_box->Draw();
		_player->Draw();
	}

	void Game::End()
	{
		EndEngine();
	}
}