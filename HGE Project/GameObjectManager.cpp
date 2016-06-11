#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include <assert.h>

GameObjectManager* GameObjectManager::myInstance = nullptr;

GameObjectManager::GameObjectManager()
{
	myNumberOfGameObjects = 0;
}

GameObjectManager::~GameObjectManager() { }

void GameObjectManager::Create()
{
	if (myInstance == nullptr)
	{
		myInstance = new GameObjectManager();
	}
}

void GameObjectManager::Destroy()
{
	delete myInstance;
	myInstance = nullptr;
}

GameObjectManager* GameObjectManager::GetInstance()
{
	if (myInstance == nullptr)
	{
		Create();
	}

	return myInstance;
}

void GameObjectManager::SetCurrentGameObject(GameObject* aObject)
{
	myCurrentGameObject = aObject;
}

GameObject* GameObjectManager::GetCurrentGameObject()
{
	return myCurrentGameObject;
}

std::map<int, GameObject*> GameObjectManager::GetAllGameObjects()
{
	return myGameObjects;
}

void GameObjectManager::DeleteGameObject(const int& aId)
{
	myGameObjects.erase(aId);
}

GameObject* GameObjectManager::GetGameObjectWithId(const int& aId)
{
	assert(myGameObjects.find(aId) != myGameObjects.end() && "WRONG ID!");
	return myGameObjects[aId];
}