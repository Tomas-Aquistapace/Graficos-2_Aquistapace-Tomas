#include "LightManager.h"

namespace Engine
{
	LightManager::LightManager()
	{

	}

	LightManager::~LightManager()
	{
		if (_directional != NULL)
		{
			delete _directional;
			_directional = NULL;
		}

		for (int i = 0; i < _pointsList.size(); i++)
		{
			if (_pointsList[i] != NULL)
			{
				delete _pointsList[i];
				_pointsList[i] = NULL;
			}
		}

		for (int i = 0; i < _spotsList.size(); i++)
		{
			if (_spotsList[i] != NULL)
			{
				delete _spotsList[i];
				_spotsList[i] = NULL;
			}
		}
	}

	// ---------

	void LightManager::AddNewDirectional(Renderer* renderer, float r, float g, float b, glm::vec3 direction)
	{
		_directional = new DirectionalLight(renderer, r, g, b, direction);
	}
	
	void LightManager::AddNewPoint(Renderer* renderer, float r, float g, float b, glm::vec3 position)
	{
		if (_pointsList.size() < MAX_INDIVIDUALS_LIGHTS)
		{
			_pointsList.push_back(new PointLight(renderer, r, g, b, position));
		}
	}
	
	void LightManager::AddNewSpot(Renderer* renderer, float r, float g, float b, glm::vec3 position, glm::vec3 direction)
	{
		if (_spotsList.size() < MAX_INDIVIDUALS_LIGHTS)
		{
			_spotsList.push_back(new SpotLight(renderer, r, g, b, position, direction));
		}
	}

	// ---------

	void LightManager::RemoveDirectional()
	{
		if (_directional != NULL)
		{
			delete _directional;
			_directional = NULL;
		}
	}

	void LightManager::RemovePoint(int i)
	{
		for (int j = 0; j < _pointsList.size(); j++)
		{
			if ((j == i) && _pointsList[j] != NULL)
			{
				delete _pointsList[j];
				_pointsList[j] = NULL;

				return;
			}
		}
	}
	
	void LightManager::RemoveSpot(int i)
	{
		for (int j = 0; j < _spotsList.size(); j++)
		{
			if ((j == i) && _spotsList[j] != NULL)
			{
				delete _spotsList[j];
				_spotsList[j] = NULL;

				return;
			}
		}
	}

	// ---------

	DirectionalLight* LightManager::GetDirectional()
	{
		if (_directional != NULL)
		{
			return _directional;
		}
	}

	PointLight* LightManager::GetPoint(int i)
	{
		for (int j = 0; j < _pointsList.size(); j++)
		{
			if ((j == i) && _pointsList[j] != NULL)
			{
				return _pointsList[j];
			}
		}
	}
	
	SpotLight* LightManager::GetSpot(int i)
	{
		for (int j = 0; j < _spotsList.size(); j++)
		{
			if ((j == i) && _spotsList[j] != NULL)
			{
				return _spotsList[j];
			}
		}
	}

	// ---------
	
	void LightManager::DrawLights()
	{
		if (_directional != NULL)
		{
			_directional->Draw(0);
		}

		for (int i = 0; i < _pointsList.size(); i++)
		{
			if (_pointsList[i] != NULL)
			{
				_pointsList[i]->Draw(i);
			}
		}

		for (int i = 0; i < _spotsList.size(); i++)
		{
			if (_spotsList[i] != NULL)
			{
				_spotsList[i]->Draw(i);
			}
		}
	}
}