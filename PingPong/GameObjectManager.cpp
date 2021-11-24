#include "pch.h"
#include "GameObjectManager.h"

void GameObjectManager::Add(int key, GameObject* value)
{
    if (objects.find(key) == objects.end())
        objects.insert({ key, value });
}

void GameObjectManager::Delete(int key)
{
    if (objects.find(key) != objects.end())
        objects.erase(key);
}

GameObject* GameObjectManager::Get(int key)
{
    return objects.find(key)->second;
}