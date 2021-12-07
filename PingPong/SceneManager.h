#pragma once
#include "Scene.h"
#include "Singleton.h"

enum class SceneType
{
	Lobby,
	Game
};

class SceneManager : 
	public Singleton::INode
{
public:
	std::shared_ptr<Scene> currentScene;
	std::map<SceneType, std::shared_ptr<Scene>> scenemap;

	SceneManager() = default;
	~SceneManager();

	void AddScene(SceneType type, std::shared_ptr<Scene> scene);
	void SetScene(SceneType type);

	std::shared_ptr<Scene> GetScene(SceneType type);
};

