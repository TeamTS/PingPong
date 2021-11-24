#pragma once
#include "GameObject.h"
class GameObjectManager
{
public:
	std::unordered_map<int, GameObject*> objects;

	void Add(int key, GameObject* value);
	void Delete(int key);
	GameObject* Get(int key);
};