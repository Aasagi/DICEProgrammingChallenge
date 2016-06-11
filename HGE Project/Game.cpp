#include "stdafx.h"
#include "Game.h"
#include "SpriteRenderCommand.h"
#include "Megaton.h"
#include "Button.h"
#include "MainMenu.h"
#include "Renderer\FontRenderCommand.h"
#include "Defines.h"

Game::Game(void)
{
}

Game::~Game(void)
{

}

void Game::Init()
{

	GenerateRandomFloor();
	myPlayer.Init();
}

void Game::Update()
{
	GameState::Update();

	for (int i = mySubStates.Size() - 1; 0 <= i; --i)
	{
		mySubStates[i]->Update();
	}

	myPlayer.Update();

	//Put code here
	Render();
}

void Game::HandleInput()
{
	myPlayer.HandleInput();
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
		Megaton::GetRenderManager()->AddCommand(myFloorTiles[floorIndex].GetRenderCommand());
	}

	myPlayer.Render();
}

void Game::GenerateRandomFloor()
{

	int numTiles = WINDOW_WIDTH / TILE_SIZE;
	myFloorTiles.Init(numTiles);
	for (int floorIndex = 0; floorIndex < numTiles; floorIndex++)
	{
		myFloorTiles.Add(FloorTile());
		myFloorTiles[floorIndex].myPosition = CU::Vector2f(floorIndex*TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE);
	}

	
}