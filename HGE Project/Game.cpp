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
	myFloorTiles.Init(START_AREA_TILE_NUMBER);
}

Game::~Game(void)
{

}

void Game::Init()
{
	myBackground1 = Megaton::GetResourceManager()->GetSprite("Data/Background/BG1.png");
	myBackground2 = Megaton::GetResourceManager()->GetSprite("Data/Background/BG2.png");
	srand(time(NULL));
	GenerateStartArea();
	myPlayer.Init();
}

void Game::Update()
{
	GameState::Update();

	for (int i = mySubStates.Size() - 1; 0 <= i; --i)
	{
		mySubStates[i]->Update();
	}

	myPlayer.Update(GetCollidingTiles(myPlayer));	

	//Put code here
	Render();
}

void Game::HandleInput()
{
	myPlayer.HandleInput();
	if (Megaton::GetInputManager()->ButtonPressed(eButton::eSPACE))
	{
		GetNextFloor();
	}
}

void Game::HandleInputWithoutGUI()
{
}

void Game::Notify(const eTriggerType& aTriggerType, void* aTrigger)
{
}

void Game::Render()
{
	SpriteRenderCommand* bgSprite = new SpriteRenderCommand(myBackground1, CU::Vector2f());

	for (int floorIndex = 0; floorIndex < myFloorTiles.Count(); floorIndex++)
	{
		myFloorTiles[floorIndex].Render();
	}

	myPlayer.Render();
}

void Game::GenerateStartArea()
{
	for (int floorIndex = 0; floorIndex < START_AREA_TILE_NUMBER; floorIndex++)
	{
		myFloorTiles.Add(FloorTile());
		myFloorTiles[myFloorTiles.Count() - 1].myPosition = CU::Vector2f(floorIndex*TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE);
	}
}

void Game::GetNextFloor()
{
	FloorTile lastTile = myFloorTiles[myFloorTiles.Count() - 1];
	int lastTileHeight = lastTile.GetTileHeight();
	
	bool recentlyMadeHole = (lastTileHeight == 0);

	for (int tileIndex = 0; tileIndex < myFloorTiles.Count() - 1; tileIndex++)
	{
		myFloorTiles[tileIndex] = myFloorTiles[tileIndex + 1];
	}

	if (recentlyMadeHole)
	{
 		lastTile.Recalculate(myFloorTiles[myFloorTiles.Count() - 3].GetTileHeight());
	}
	else
	{
		if (rand() % 2 == 0)
		{
			lastTile.Recalculate(0);
		}
		else if (lastTileHeight < 5 && rand()%3 == 0)
		{
			lastTile.Recalculate(++lastTileHeight);
		}
		else if (lastTileHeight > 0 && rand() % 5 == 0)
		{
			lastTile.Recalculate(--lastTileHeight);
		}
	}
	lastTile.myPosition += CU::Vector2f(TILE_SIZE, 0.0f);
	myFloorTiles[myFloorTiles.Count() - 1] = lastTile;
}

CU::GrowingArray<FloorTile> Game::GetCollidingTiles(Avatar& player)
{
	auto avatarAABB = player.GetAABB();
	auto result = CU::GrowingArray<FloorTile>();

	auto tileCount = myFloorTiles.Count();
	result.Init(tileCount);
	for (auto tileIndex = 0; tileIndex < tileCount; tileIndex++)
	{
		auto tile = myFloorTiles[tileIndex];
		auto tileAABB = tile.GetAABB();

		if (avatarAABB.Collides(tileAABB))
		{
			result.Add(tile);
		}		
	}

	return result;
}
