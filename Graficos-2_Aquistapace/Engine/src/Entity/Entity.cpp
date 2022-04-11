#include "Entity.h"

namespace Engine
{
	Entity::Entity()
	{
		//_renderer = renderer;

		SetPosition(0,0,0);
		SetRotation(0,0,0);
		SetScale(1,1,1);

		SetPrebPosition(_transform.position);
		SetPrebRotation(_transform.rotation);
		SetPrebScale(_transform.scale);

		_isTrigger = false;
		_isStatic = false;
		_isHableToDraw = true;
	}

	Entity::~Entity()
	{

	}

	void Entity::SetPosition(float x, float y, float z)
	{
		SetPrebPosition(_transform.position);

		_transform.position.x = x;
		_transform.position.y = y;
		_transform.position.z = z;

		_generalMatrix.translate = glm::translate(glm::mat4(1.0f), _transform.position);
		UpdateMatrix();
	}
	
	void Entity::SetPosition(glm::vec3 position)
	{
		SetPrebPosition(_transform.position);

		_transform.position = position;

		_generalMatrix.translate = glm::translate(glm::mat4(1.0f), _transform.position);
		UpdateMatrix();
	}

	void Entity::Move(float speed, glm::vec3 direction)
	{
		SetPosition(_transform.position += speed * direction);
	}

	void Entity::SetRotation(float x, float y, float z)
	{
		SetPrebRotation(_transform.rotation);

		_transform.rotation = { x, y, z };
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrix();
		UpdateTransformsData();
	}
	
	void Entity::SetRotation(glm::vec3 rotation)
	{
		SetPrebRotation(_transform.rotation);

		_transform.rotation = rotation;
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrix();
		UpdateTransformsData();
	}

	void Entity::SetRotationX(float x)
	{
		SetPrebRotationX(0);

		_transform.rotation.x = x;
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		UpdateMatrix();
		UpdateTransformsData();
	}
	
	void Entity::SetRotationY(float y)
	{
		SetPrebRotationY(0);

		_transform.rotation.y = y;
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		UpdateMatrix();
		UpdateTransformsData();
	}
	
	void Entity::SetRotationZ(float z)
	{
		SetPrebRotationZ(0);

		_transform.rotation.z = z;
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrix();
		UpdateTransformsData();
	}

	void Entity::Rotate(glm::vec3 rotation)
	{
		SetPrebRotation(_transform.rotation);

		_transform.rotation += rotation;
		_generalMatrix.rotateX += glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		_generalMatrix.rotateY += glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		_generalMatrix.rotateZ += glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		UpdateMatrix();
		UpdateTransformsData();
	}

	void Entity::SetScale(float x, float y, float z) 
	{
		SetPrebScale(_transform.scale);

		_transform.scale.x = x;
		_transform.scale.y = y;
		_transform.scale.z = z;

		_generalMatrix.scale = glm::scale(glm::mat4(1.0f), _transform.scale);
		UpdateMatrix();
	}
	
	void Entity::SetScale(glm::vec3 scale)
	{
		SetPrebScale(_transform.scale);

		_transform.scale = scale;

		_generalMatrix.scale = glm::scale(glm::mat4(1.0f), _transform.scale);
		UpdateMatrix();
	}

	void Entity::HableToDraw(bool state)
	{
		_isHableToDraw = state;
	}

	// --------------------------------
	// Se utiliza para poder updatear la matris "model" que controla todas posiciones y datos de la figura
	
	void Entity::UpdateMatrix() 
	{
		_generalMatrix.model = _generalMatrix.translate * 
							   _generalMatrix.rotateX * 
							   _generalMatrix.rotateY *
							   _generalMatrix.rotateZ * 
							   _generalMatrix.scale;
	}
	
	void Entity::ReturnToPrevTransform()
	{
		SetPosition(_transform.preb_position);
		SetRotation(_transform.preb_rotation);
		SetScale(_transform.preb_scale);
	}

	void Entity::ReturnToPrevPosition()
	{
		SetPosition(_transform.preb_position);
	}

	void Entity::ReturnToPrevRotation()
	{
		SetRotation(_transform.preb_rotation);
	}
	
	void Entity::ReturnToPrevScale()
	{
		SetScale(_transform.preb_scale);
	}

	// --------------------------------
	// Se utiliza para las colisiones

	void Entity::SetTriggerState(bool state)
	{
		_isTrigger = state;
	}

	void Entity::SetStaticState(bool state)
	{
		_isStatic = state;
	}

	bool Entity::GetTriggerState()
	{
		return _isTrigger;
	}

	bool Entity::GetStaticState()
	{
		return _isStatic;
	}

	//---------------------------------
	// Gets de las Direcciones:

	glm::vec3 Entity::GetPosition()
	{
		return _transform.position;
	}

	glm::vec3 Entity::GetFront()
	{
		return _transform.forward;
	}
	glm::vec3 Entity::GetUp()
	{
		return _transform.up;
	}
	glm::vec3 Entity::GetRight()
	{
		return _transform.right;
	}

	Entity* Entity::GetEntity()
	{
		return this;
	}

	bool Entity::GetHableToDraw()
	{
		return _isHableToDraw;
	}

	// --------------------------------
	// Funciones usadas para setear las posiciones anteriores antes de hacer un SetPos, etc
	void Entity::SetPrebPosition(glm::vec3 position)
	{
		_transform.preb_position = position;
	}
	
	void Entity::SetPrebRotation(glm::vec3 rotation)
	{
		_transform.preb_rotation = rotation;
	}
	
	void Entity::SetPrebRotationX(float x)
	{
		_transform.preb_rotation.x = x;
	}
	
	void Entity::SetPrebRotationY(float y)
	{
		_transform.preb_rotation.y = y;
	}
	
	void Entity::SetPrebRotationZ(float z)
	{
		_transform.preb_rotation.z = z;
	}
	
	void Entity::SetPrebScale(glm::vec3 scale)
	{
		_transform.preb_scale = scale;
	}

	// ----------------------------------
	// Protected Functions:

	float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;

	glm::quat EulerToQuat(glm::vec3 euler) {
		euler *= deg2rad;

		float cy = cos(euler.z * 0.5);
		float sy = sin(euler.z * 0.5);
		float cp = cos(euler.x * 0.5);
		float sp = sin(euler.x * 0.5);
		float cr = cos(euler.y * 0.5);
		float sr = sin(euler.y * 0.5);

		glm::quat q;
		q.w = cr * cp * cy + sr * sp * sy;
		q.x = cr * sp * cy + sr * cp * sy;
		q.y = sr * cp * cy - cr * sp * sy;
		q.z = cr * cp * sy - sr * sp * cy;
		return q;
	}

	glm::vec3 QuatXVec(glm::quat quat, glm::vec3 vec) {
		float x2 = quat.x * 2.0f;
		float y2 = quat.y * 2.0f;
		float z2 = quat.z * 2.0f;
		float xx2 = quat.x * x2;
		float yy2 = quat.y * y2;
		float zz2 = quat.z * z2;
		float xy2 = quat.x * y2;
		float xz2 = quat.x * z2;
		float yz2 = quat.y * z2;
		float wx2 = quat.w * x2;
		float wy2 = quat.w * y2;
		float wz2 = quat.w * z2;

		glm::vec3 res;
		res.x = (1.0f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
		res.y = (xy2 + wz2) * vec.x + (1.0f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
		res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.0f - (xx2 + yy2)) * vec.z;
		return res;
	}

	void Entity::UpdateTransformsData()
	{
		_transform.rotationQuaternion = EulerToQuat(_transform.rotation);
		_transform.forward = QuatXVec(_transform.rotationQuaternion, glm::vec3(0, 0, 1));
		_transform.up = QuatXVec(_transform.rotationQuaternion, glm::vec3(0, 1, 0));
		_transform.right = QuatXVec(_transform.rotationQuaternion, glm::vec3(1, 0, 0));
	}
}