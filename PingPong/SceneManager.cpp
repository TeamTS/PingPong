#include "pch.h"
#include "SceneManager.h"

SceneManager::~SceneManager()
{
}

void SceneManager::AddScene(SceneType type, std::shared_ptr<Scene> scene)
{
	if (scenemap.find(type) == scenemap.end())
	{
		scenemap.emplace(type, scene);
	}
}

void SceneManager::SetScene(SceneType type)
{
	currentScene = scenemap[type];
	currentScene->Initialize();
}

std::shared_ptr<Scene> SceneManager::GetScene(SceneType type)
{
	assert(scenemap.find(type) != scenemap.end());
	return scenemap[type];
}
