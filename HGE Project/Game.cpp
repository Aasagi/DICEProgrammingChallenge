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
	myCurrentState = ePlaying;
	holePassCounter = 0;
	tilesPassed = 0;
}

Game::~Game(void)
{

}

void Game::Init()
{
	myBackground1 = Megaton::GetResourceManager()->GetSprite("Data/Background/BG1.png");
	myBackground1->SetTextureRect(0, 0, 800, 600);
	myBackground2 = Megaton::GetResourceManager()->GetSprite("Data/Background/BG2.png");
	myBackground2->SetTextureRect(0, 0, 800, 600,false);

	srand(time(NULL));
	GenerateStartArea();
	myPlayer.Init();
	myGoalObject.SetPosition(CU::Vector2f(-100.0f, -100.0f));
}

void Game::Update()
{
	GameState::Update();
	
	for (int i = mySubStates.Size() - 1; 0 <= i; --i)
	{
		mySubStates[i]->Update();
	}

	if (myCurrentState == ePlaying)
	{
		if (myPlayer.GetAABB().Collides(myGoalObject.GetAABB()))
		{
			myCurrentState = eWin;
		}
		myPlayer.Update(GetCollidingTiles(myPlayer));
		if (myPlayer.myPosition.x > WINDOW_WIDTH / 2.f)
		{
			myCamera.myPositionOffset.x = myPlayer.myPosition.myX - WINDOW_WIDTH / 2.f;
		}
	}

	int halfTileCount = myFloorTiles.Count() / 2;
	if (tilesPassed < TILES_PASS_TO_GOAL && myPlayer.GetPosition().x > myFloorTiles[halfTileCount].GetPosition().x)
	{
		if (myFloorTiles[halfTileCount].GetTileHeight() == 0)
		{
			holePassCounter++;
			if (holePassCounter >= 10)
			{
				myCurrentState = eWin;
			}
		}
		tilesPassed++;
		GetNextFloor();
	}
	
	//Put code here
	Render();
}

void Game::HandleInput()
{
	myPlayer.HandleInput();
	if (Megaton::GetInputManager()->ButtonPressed(eButton::eI))
	{
		myCurrentState = eGameover;
	}
	if (Megaton::GetInputManager()->ButtonPressed(eButton::eK))
	{
		myCurrentState = eWin;
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

	SpriteRenderCommand* bgSprite = new SpriteRenderCommand(myBackground1, myCamera.ConvertPositionToCameraPosition(CU::Vector2f(0,WINDOW_WIDTH)));
	SpriteRenderCommand* bgSprite1 = new SpriteRenderCommand(myBackground1, myCamera.ConvertSquarePositionToCameraPosition(CU::Vector2f(0, 0)));

	if (myCurrentState != ePlaying)
	{
		switch (myCurrentState)
		{
		case ePlaying:
			break;
		case eGameover:
		{
			FontRenderCommand* fontRender = new FontRenderCommand(std::string("GAME OVER"), Megaton::GetResourceManager()->GetFont(), CU::Vector2f(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2));
			fontRender->SetColor(ARGB(200, 0, 0, 0));
			Megaton::GetRenderManager()->AddCommand(fontRender);
			break;
		}
		case eWin:
		{
			FontRenderCommand* fontRender = new FontRenderCommand(std::string("A WINNER IS YOU"), Megaton::GetResourceManager()->GetFont(), CU::Vector2f(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2));
			fontRender->SetColor(ARGB(200, 0, 0, 0));
			Megaton::GetRenderManager()->AddCommand(fontRender);
			break;

		}
		default:
			break;
		}
	}


	for (int floorIndex = 0; floorIndex < myFloorTiles.Count(); floorIndex++)
	{
		myFloorTiles[floorIndex].Render(myCamera);
	}

	FontRenderCommand* fontRender = new FontRenderCommand(std::string("Score: ") + std::to_string(holePassCounter), Megaton::GetResourceManager()->GetFont(), CU::Vector2f(20.0f, 20.0f));
	fontRender->SetColor(ARGB(200, 0, 0, 0));
	Megaton::GetRenderManager()->AddCommand(fontRender);

	myPlayer.Render(myCamera);
	myGoalObject.Render(myCamera);
	Megaton::GetRenderManager()->AddCommand(bgSprite);
	Megaton::GetRenderManager()->AddCommand(bgSprite1);
}

void Game::GenerateStartArea()
{
	for (int floorIndex = 0; floorIndex < START_AREA_TILE_NUMBER; floorIndex++)
	{
		myFloorTiles.Add(FloorTile());
		myFloorTiles[myFloorTiles.Count() - 1].SetPosition(CU::Vector2f(floorIndex*TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE));
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

	lastTile.SetPosition(lastTile.GetPosition() + CU::Vector2f(TILE_SIZE, 0.0f));
	if (tilesPassed >= TILES_PASS_TO_GOAL)
	{
		int indexToCheck = recentlyMadeHole ? myFloorTiles.Count() - 3 : myFloorTiles.Count() - 2;
		lastTile.Recalculate(myFloorTiles[indexToCheck].GetTileHeight());

		myGoalObject.SetPosition(lastTile.GetPosition() - CU::Vector2f(0.0f, lastTileHeight * TILE_SIZE));
	}
	else if (recentlyMadeHole)
	{
		lastTile.Recalculate(myFloorTiles[myFloorTiles.Count() - 3].GetTileHeight());
	}
	else
	{
		if (rand() % 20 == 0)
		{
			lastTile.Recalculate(0);
		}
		else if (lastTileHeight < 5 && rand() % 5 == 0)
		{
			lastTile.Recalculate(++lastTileHeight);
		}
		else if (lastTileHeight > 0 && rand() % 5 == 0)
		{
			lastTile.Recalculate(--lastTileHeight);
		}
	}
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
