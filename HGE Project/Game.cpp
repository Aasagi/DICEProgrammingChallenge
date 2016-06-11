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
	myBackground1 = Megaton::GetResourceManager()->GetSprite("Data/Background/BG1.png");
	myBackground2 = Megaton::GetResourceManager()->GetSprite("Data/Background/BG2.png");
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

	myPlayer.Update();
	if (myPlayer.myPosition.x > WINDOW_WIDTH/2.f)
	{
		myCamera.myPositionOffset.x = myPlayer.myPosition.myX - WINDOW_WIDTH/2.f;
	}
	
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
	SpriteRenderCommand* bgSprite = new SpriteRenderCommand(myBackground1, CU::Vector2f());
	SpriteRenderCommand* bgSprite2 = new SpriteRenderCommand(myBackground2, CU::Vector2f());


	
	for (int floorIndex = 0; floorIndex < myFloorTiles.Count(); floorIndex++)
	{
		CU::Vector2f postion = 	myCamera.ConvertPositionToCameraPosition(myFloorTiles[floorIndex].myPosition);
		SpriteRenderCommand* floor = new SpriteRenderCommand(*myFloorTiles[floorIndex].GetRenderCommand());
		floor->SetPosition(postion);
		Megaton::GetRenderManager()->AddCommand(floor);
	}

	myPlayer.Render(myCamera);
	Megaton::GetRenderManager()->AddCommand(bgSprite);
	Megaton::GetRenderManager()->AddCommand(bgSprite2);
}





void Game::GenerateRandomFloor()
{
	bool recentlyMadeHole = false;
	int lastTileHeight = 1;

	int numTiles = WINDOW_WIDTH *2 / TILE_SIZE;
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