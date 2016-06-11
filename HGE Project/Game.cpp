#include "stdafx.h"
#include "Game.h"
#include "hgesprite.h"
#include "SpriteRenderCommand.h"
#include "Megaton.h"
#include "Button.h"
#include "MainMenu.h"
#include "Renderer\FontRenderCommand.h"

#define WINDOW_WIDTH 800.0f
#define WINDOW_HEIGHT 600.0f
#define TILE_SIZE 20.0f

Game::Game(void)
{
}

Game::~Game(void)
{

}

void Game::Init()
{

	GenerateRandomFloor();
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
		Megaton::GetRenderManager()->AddCommand(myFloorTiles[floorIndex].GetRenderCommand());
	}

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