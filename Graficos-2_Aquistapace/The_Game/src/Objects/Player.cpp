#include "Player.h"

namespace Engine
{
	Player::Player(Renderer* renderer, const glm::ivec2& tileDimensions, float speed) : Sprite(renderer, tileDimensions)
	{
		_speed = speed;
	}
	
	Player::~Player()
	{

	}

	void Player::Move(float deltaTime)
	{
		if (Input::GetKey(Keycode::W))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(180);

			SetPosition(_transform.position.x, _transform.position.y + (_speed * deltaTime), _transform.position.z);
		}
		else if (Input::GetKey(Keycode::S))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(0);

			SetPosition(_transform.position.x, _transform.position.y - (_speed * deltaTime), _transform.position.z);
		}
		else if (Input::GetKey(Keycode::A))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(180);
		
			SetPosition(_transform.position.x - (_speed * deltaTime), _transform.position.y, _transform.position.z);
		}
		else if (Input::GetKey(Keycode::D))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(0);
		
			SetPosition(_transform.position.x + (_speed * deltaTime), _transform.position.y, _transform.position.z);
		}
		else
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVs(36));
		}
	}

	void Player::TriggerCollision(Entity* other)
	{
		if (!other->GetStaticState())
		{
			glm::vec3 newPos = _transform.position;
			ReturnToPrevPosition();
			newPos -= _transform.position;

			other->SetPosition(other->_transform.position + newPos);
		}
		else
		{
			ReturnToPrevPosition();
		}
	}
}