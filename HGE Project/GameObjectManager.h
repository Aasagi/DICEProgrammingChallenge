#pragma once

#include <map>

class GameObject;
class GameObjectManager
{
public:
	static void Create();
	static void Destroy();
	static GameObjectManager* GetInstance();

	void SetCurrentGameObject(GameObject* aObject);
	GameObject* GetCurrentGameObject();
	GameObject* GetGameObjectWithId(const int& aId);
	std::map<int, GameObject*> GetAllGameObjects();
	void DeleteGameObject(const int& aId);

private:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* myInstance;

	GameObject* myCurrentGameObject;
	std::map<int, GameObject*> myGameObjects;
	int myNumberOfGameObjects;
};

