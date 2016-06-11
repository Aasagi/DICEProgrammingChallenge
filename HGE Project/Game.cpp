#include "stdafx.h"
#include "Game.h"
#include "SpriteRenderCommand.h"
#include "Megaton.h"
#include "Button.h"
#include "time.h"
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
	srand(time(NULL));
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

	myPlayer.HandleCollision(GetCollidingTiles(myPlayer));
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
	bool recentlyMadeHole = false;
	int lastTileHeight = 1;

	int numTiles = WINDOW_WIDTH / TILE_SIZE;
	myFloorTiles.Init(numTiles);
	for (int floorIndex = 0; floorIndex < numTiles; floorIndex++)
	{
		bool makeFloor = false;

		if (floorIndex < START_AREA_TILE_NUMBER)
		{
			makeFloor = true;
			lastTileHeight = 1;
		}
		else if (recentlyMadeHole)
		{
			makeFloor = true;
		}

		if (makeFloor == false)
		{
			int randomTile = rand();
			if (randomTile % 2 == 0)
			{
				makeFloor = true;

				if (lastTileHeight < 5 && randomTile % 3 == 0 )
				{
					lastTileHeight++;
				}
				else if (lastTileHeight > 1 && randomTile % 5 == 0)
				{
					lastTileHeight--;
				}
			}
			else
			{
				recentlyMadeHole = true;
			}
		}

		if (makeFloor)
		{
			recentlyMadeHole = false;
			for (int tileHeightIndex = 1; tileHeightIndex <= lastTileHeight; tileHeightIndex++)
			{
				myFloorTiles.Add(FloorTile());
				myFloorTiles[myFloorTiles.Count() - 1].myPosition = CU::Vector2f(floorIndex*TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE * tileHeightIndex);
			}
		}

	}

	
}

CU::GrowingArray<FloorTile> Game::GetCollidingTiles(Avatar& player)
{
	auto avatarAABB = player.GetAABB();
	auto result = CU::GrowingArray<FloorTile>();

	auto tileCount = myFloorTiles.Count();
	for (auto tileIndex = 0; tileIndex < tileCount; tileIndex++);
	{
		auto tile = myFloorTiles[tileCount];
		auto tileAABB = tile.GetAABB();

		if (avatarAABB.Collides(tileAABB))
		{
			result.Add(tile);
		}		
	}
}
