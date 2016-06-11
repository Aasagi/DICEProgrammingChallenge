#include "stdafx.h"
#include "Game.h"
#include "hgesprite.h"
#include "SpriteRenderCommand.h"
#include "Megaton.h"
#include "Button.h"
#include "MainMenu.h"
#include "Renderer\FontRenderCommand.h"
Game::Game(void)
{
}

Game::~Game(void)
{

}

void Game::Init()
{
	Megaton::GetResourceManager()->GetSprite("Data/node.png");
	myFloorSprite = Megaton::GetResourceManager()->GetSprite("Data/nodeCube.png");

	int numTiles = 12;
	myFloorTiles.Init(numTiles);
	for (int floorIndex = 0; floorIndex < numTiles; floorIndex++)
	{ 
		myFloorTiles.Add(FloorTile());
		myFloorTiles[floorIndex].myPosition = CU::Vector2f(floorIndex*64.0f, 500.0f);
	}
}

void Game::Update()
{
	GameState::Update();

	for (int i = mySubStates.Size() - 1; 0 <= i; --i)
	{
		mySubStates[i]->Update();
	}


	//Put code here
	Render();
}

void Game::HandleInput()
{

}

void Game::HandleInputWithoutGUI()
{
}

void Game::Notify(const eTriggerType& aTriggerType, void* aTrigger)
{
}

void Game::Render()
{
	for (int floorIndex = 0; floorIndex < myFloorTiles.Count(); floorIndex++)
	{
		SpriteRenderCommand* spriteRenderCommand = new SpriteRenderCommand(myFloorSprite, myFloorTiles[floorIndex].myPosition);
		Megaton::GetRenderManager()->AddCommand(spriteRenderCommand);
	}

}