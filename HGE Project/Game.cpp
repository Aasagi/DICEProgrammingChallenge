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
	myCeilingTiles.Init(START_AREA_TILE_NUMBER);
	myHangingObjects.Init(5);
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
	myBackground2->SetTextureRect(0, 0, 800, 600, false);

	srand(time(NULL));
	GenerateStartArea();
	for (int hangingObjectIndex = 0; hangingObjectIndex < 5; hangingObjectIndex++)
	{
		myHangingObjects.Add(HangingObject());
	}
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
		myCamera.myPositionOffset.x += 0.1f;// myPlayer.myPosition.myX - WINDOW_WIDTH / 2.f;
		myPlayer.Update(GetCollidingTiles(myPlayer));

	
		if (myPlayer.myPosition.x - myCamera.myPositionOffset.x <= 0 || myPlayer.myPosition.y - myPlayer.GetAABB().GetHeight() > WINDOW_HEIGHT)
		{
			myCurrentState = eGameover;
		}
	}

	auto halfTileCount = myFloorTiles.Count() / 2;
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

	for (int hangingObjectIndex = 0; hangingObjectIndex < myHangingObjects.Count(); hangingObjectIndex++)
	{
		if (myPlayer.GetAABB().Collides(myHangingObjects[hangingObjectIndex].GetAABB()))
		{
			myCurrentState = eGameover;
		}

		if (myHangingObjects[hangingObjectIndex].OnScreen && myHangingObjects[hangingObjectIndex].GetPostion().x < myCeilingTiles[0].GetPosition().x)
		{
			myHangingObjects[hangingObjectIndex].OnScreen = false;
			myHangingObjects[hangingObjectIndex].SetPosition(CU::Vector2f(-100.0f, -100.0f));
		}
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

	SpriteRenderCommand* bgSprite = new SpriteRenderCommand(myBackground1, myCamera.ConvertPositionToCameraPosition(CU::Vector2f(0, WINDOW_WIDTH)));
	SpriteRenderCommand* bgSprite1 = new SpriteRenderCommand(myBackground1, myCamera.ConvertSquarePositionToCameraPosition(CU::Vector2f(0, 0)));




	for (int floorIndex = 0; floorIndex < myFloorTiles.Count(); floorIndex++)
	{
		myFloorTiles[floorIndex].Render(myCamera);
		myCeilingTiles[floorIndex].Render(myCamera);
	}
	for (int hangingObjectIndex = 0; hangingObjectIndex < myHangingObjects.Count(); hangingObjectIndex++)
	{
		myHangingObjects[hangingObjectIndex].Render(myCamera);
	}
	myPlayer.Render(myCamera);
	myGoalObject.Render(myCamera);

	FontRenderCommand* fontRender = new FontRenderCommand(std::string("Score: ") + std::to_string(holePassCounter), Megaton::GetResourceManager()->GetFont(), CU::Vector2f(20.0f, 20.0f));
	fontRender->SetColor(ARGB(200, 0, 0, 0));
	Megaton::GetRenderManager()->AddCommand(fontRender);


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


	Megaton::GetRenderManager()->AddCommand(bgSprite);
	Megaton::GetRenderManager()->AddCommand(bgSprite1);
}

void Game::GenerateStartArea()
{
	for (int floorIndex = 0; floorIndex < START_AREA_TILE_NUMBER; floorIndex++)
	{
		myFloorTiles.Add(FloorTile());
		myCeilingTiles.Add(FloorTile());

		myFloorTiles[myFloorTiles.Count() - 1].SetPosition(CU::Vector2f(floorIndex*TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE));
		myCeilingTiles[myCeilingTiles.Count() - 1].SetPosition(CU::Vector2f(floorIndex*TILE_SIZE, WINDOW_HEIGHT - TILE_SIZE - AVATAR_HEIGHT * 3));
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
		myCeilingTiles[tileIndex] = myCeilingTiles[tileIndex + 1];
	}

	lastTile.SetPosition(lastTile.GetPosition() + CU::Vector2f(TILE_SIZE, 0.0f));
	myCeilingTiles[myCeilingTiles.Count() - 1].SetPosition(myCeilingTiles[myCeilingTiles.Count() - 1].GetPosition() + CU::Vector2f(TILE_SIZE, 0.0f));
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
		/*if (rand() % 20 == 0)
		{
		lastTile.Recalculate(0);
		}
		else */if (lastTileHeight < 5 && rand() % 5 == 0)
		{
		lastTile.Recalculate(++lastTileHeight);
		}
		else if (lastTileHeight > 1 && rand() % 5 == 0)
		{
			lastTile.Recalculate(--lastTileHeight);
		}
	}
	myFloorTiles[myFloorTiles.Count() - 1] = lastTile;
	if (lastTile.GetTileHeight() <= 1)
	{
		myCeilingTiles[myCeilingTiles.Count() - 1].Recalculate(1);
		if (rand() % 10 == 0)
		{
			for (int hangingObjectIndex = 0; hangingObjectIndex < myHangingObjects.Count(); hangingObjectIndex++)
			{
				if (myHangingObjects[hangingObjectIndex].OnScreen == false)
				{
					myHangingObjects[hangingObjectIndex].OnScreen = true;
					myHangingObjects[hangingObjectIndex].SetPosition(myCeilingTiles[myCeilingTiles.Count() - 1].GetPosition() + CU::Vector2f(0.0f, TILE_SIZE));
				}
			}
		}
	}
	else
	{
		myCeilingTiles[myCeilingTiles.Count() - 1].Recalculate(0);
	}
}

CU::GrowingArray<FloorTile> Game::GetCollidingTiles(Avatar& player)
{
	auto avatarAABB = player.GetAABB();
	auto result = CU::GrowingArray<FloorTile>();

	auto tileCount = myFloorTiles.Count();
	result.Init(tileCount * 2);
	for (auto tileIndex = 0; tileIndex < tileCount; tileIndex++)
	{
		auto tile = myFloorTiles[tileIndex];
		auto tileAABB = tile.GetAABB();

		if (avatarAABB.Collides(tileAABB))
		{
			result.Add(tile);
		}
	}
	for (auto tileIndex = 0; tileIndex < tileCount; tileIndex++)
	{
		auto tile = myCeilingTiles[tileIndex];
		auto tileAABB = tile.GetAABB();

		if (avatarAABB.Collides(tileAABB))
		{
			result.Add(tile);
		}
	}
	return result;
}
