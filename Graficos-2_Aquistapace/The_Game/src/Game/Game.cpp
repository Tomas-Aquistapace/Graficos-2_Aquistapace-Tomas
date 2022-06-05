#include "Game.h"
#include <iostream>
#include <time.h>

namespace Engine
{
	Game::Game(): GameBase()
	{
		_floor = NULL;
		_box = NULL;

		_cameraGame = NULL;

		_lightCube = NULL;
		_actualLight = NULL;

		for (Cube* item : _walls)
		{
			item = NULL;
		}
	}

	Game::~Game()
	{
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
		
		if (_actualLight != NULL)
		{
			delete _actualLight;
			_actualLight = NULL;
		}
		if (_lightCube != NULL)
		{
			delete _lightCube;
			_lightCube = NULL;
		}

		for (Cube* item : _walls)
		{
			if (item != NULL)
			{
				delete item;
				item = NULL;
			}
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
		ActivateFPSCamera(_cameraGame, 0.05f);
		
		// --------------------------------

		_lightCube = new Cube(GetRenderer());
		_lightCube->InitTexture("res/super-mario-question-block.png", NULL);
		_lightCube->SetPosition(2, 1, -2);
		// Pearl:
		//_lightCube->SetMaterial(glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f);

		_actualLight = new Light(GetRenderer(), 1,1,1, LightType::Directional);
		_actualLight->SetDirectionData(glm::vec3(-0.2f, -1.0f, -0.3f));
		//_actualLight->SetPosition(_lightCube->GetPosition());

		// --------------------------------

		_floor = new Sprite(GetRenderer());
		_floor->InitTexture("res/camouflage.png");
		_floor->SetPosition(0, -1.2, 0);
		_floor->SetRotationX(90);
		_floor->SetScale(glm::vec3(20,20,20));
		_floor->SetStaticState(true);
		GetCollisionManager()->AddNewObject(_floor);


		_player = new Cube(GetRenderer());
		_player->InitTexture("res/BOB-ESPONJA-1-22.png", NULL);
		_player->SetScale(0.7f, 1, 0.7f);
		_player->SetPosition(0, 0, 5);
		//GetCollisionManager()->AddNewObject(_player);

		// --------------------------------

		_box = new Cube(GetRenderer());
		_box->InitTexture("res/container2.png", "res/container2_specular.png");
		_box->SetPosition(0,0,0);
		//_box->SetMaterial(glm::vec3(0.1745f, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f,	0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.6f);
		//GetCollisionManager()->AddNewObject(_box);

		// --------------------------------

		for (int i = 0; i < COUNT_WALLS; i++)
		{
			_walls[i] = new Cube(GetRenderer());
			_walls[i]->InitTexture("res/wall.jpg", NULL);
			_walls[i]->SetScale(2,3,2);
		}
		_walls[0]->SetPosition(4,0,4);
		_walls[1]->SetPosition(4,0,-4);
		_walls[2]->SetPosition(-4,0,4);
		_walls[3]->SetPosition(-4,0,-4);
	}
	
	void Game::Play()
	{
		UpdateEngine(0.2f, 0.2f, 0.2f, 1);
	}

	void Game::Update(float deltaTime)
	{
		if (Input::GetKey(Keycode::W))
		{
			_player->SetPosition(_player->_transform.position - (_player->_transform.forward * (cameraSpeed * deltaTime)));
		}
		if (Input::GetKey(Keycode::S))
		{
			_player->SetPosition(_player->_transform.position + (_player->_transform.forward * (cameraSpeed * deltaTime)));
		}
		if (Input::GetKey(Keycode::A))
		{
			_player->SetPosition(_player->_transform.position - (_player->_transform.right * (cameraSpeed * deltaTime)));
		}
		if (Input::GetKey(Keycode::D))
		{
			_player->SetPosition(_player->_transform.position + (_player->_transform.right * (cameraSpeed * deltaTime)));
		}


		//_actualLight->SetPosition(_player->GetPosition());


		if (Input::GetKeyDown(Keycode::SPACE))
		{
			if (!cameraType)
			{
				DeactivateFPSCamera();
			}
			else
			{
				ActivateFPSCamera(_cameraGame, 0.05f);
			}

			cameraType = !cameraType;
		}


		if(!cameraType)
			_cameraGame->FirstPerson(_player->GetEntity(), false);
		else
			_cameraGame->ThirdPerson(_player->GetEntity(), glm::vec3(4,3,4), true);
		
		//_cameraGame->UpdateView();


		_box->SetRotation(_box->_transform.rotation - (30 * deltaTime));


		//GetCollisionManager()->CheckAllCollisions();

		for (Cube* item : _walls)
		{
			item->Draw();
		}
		_floor->Draw();
		_box->Draw();
		_player->Draw();
		_actualLight->Draw();
		_lightCube->Draw();
	}

	void Game::End()
	{
		EndEngine();
	}
}