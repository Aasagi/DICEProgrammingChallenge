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
	myAITurn = false;
}

Game::~Game(void)
{

}

void Game::Init()
{
	myRandomScore = 0;
	myChoiceScore = 0;
	Megaton::GetResourceManager()->GetSprite("Data/node.png");
	myNodeSprite = Megaton::GetResourceManager()->GetSprite("Data/node.png");
	myVertSprite = Megaton::GetResourceManager()->GetSprite("Data/nodeHori.png");
	myHoriSprite = Megaton::GetResourceManager()->GetSprite("Data/nodeLong.png");
	myCubeSprite = Megaton::GetResourceManager()->GetSprite("Data/nodeCube.png");

	mySquare.Init(16);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Square sq;
			sq.myPosition = CU::Vector2i(i, j);
			mySquare.Add(sq);
		}
	}


}

void Game::Update()
{
	GameState::Update();

	for (int i = mySubStates.Size() - 1; 0 <= i; --i)
	{
		mySubStates[i]->Update();
	}
	bool hasFinished = true;
	for (int i = 0; i < mySquare.Size(); i++)
	{
		if (mySquare[i].myIsTaken == false)
		{
			hasFinished = false;
		}
	}
	myUpdateTimer -= Megaton::GetTimerManager()->GetFrameTime().AsSeconds();
	if (hasFinished == false && myUpdateTimer < 0)
	{
		if (myAITurn == false)
		{
			UpdateRandom();
			myAITurn = true;
		}
		else
		{
			UpdateChoice();
			myAITurn = false;
		}
		myUpdateTimer = 1.f;
	}


	//Put code here
	Render();
}

void Game::HandleInput()
{

}

void Game::UpdateRandom()
{
	bool hasMadeChoice = false;

	while (hasMadeChoice == false)
	{
		int randomx = rand() % 4;
		int randomy = rand() % 4;

		int randomx2 = (rand() % 4);


		if (CheckIfLineExists(CU::Vector2i(randomx, randomy), randomx2) == false)//Linedoesnotexist)
		{
			int index = FindIndex(randomx, randomy);
			if (index == -1)
			{
				continue;
			}



			switch (randomx2)
			{
			case 0:
			{
				mySquare[index].myDown = true;
				CU::Vector2i pos = mySquare[index].myPosition + CU::Vector2i(0, 1);
				int i = FindIndex(pos.x, pos.y);
				if (i != -1)
				{
					mySquare[i].myUp = true;
				}
			}
			break;
			case 1:
			{
				mySquare[index].myRight = true;
				CU::Vector2i pos = mySquare[index].myPosition + CU::Vector2i(1, 0);
				int i = FindIndex(pos.x, pos.y);
				if (i != -1)
				{
					mySquare[i].myLeft = true;
				}

				break;
			}
			case 2:
			{
				mySquare[index].myUp = true;
				CU::Vector2i pos = mySquare[index].myPosition + CU::Vector2i(0, -1);
				int i = FindIndex(pos.x, pos.y);
				if (i != -1)
				{
					mySquare[i].myDown = true;
				}
				break;
			}
			case 3:
			{
				mySquare[index].myLeft = true;
				CU::Vector2i pos = mySquare[index].myPosition + CU::Vector2i(-1, 0);
				int i = FindIndex(pos.x, pos.y);
				if (i != -1)
				{
					mySquare[i].myRight = true;
				}

				break;
			}
			default:
				break;
			}
			hasMadeChoice = true;
		}
	}
	int inds = WinCheck();
	if (inds != 0)
	{
		myRandomScore += inds;
	}
}

void Game::UpdateChoice()
{
	int largestIndex = 0;
	int size = 0;
	for (int i = 0; i < mySquare.Size(); i++)
	{
		int counted = CountTaken(i);
		if (counted > size && counted != 2 && counted != 4)
		{
			largestIndex = i;
			size = counted;
		}
	}
	if (mySquare[largestIndex].myDown == false)
	{
		mySquare[largestIndex].myDown = true;
		CU::Vector2i pos = mySquare[largestIndex].myPosition + CU::Vector2i(0, 1);
		int i = FindIndex(pos.x, pos.y);
		if (i != -1)
		{
			mySquare[i].myUp = true;
		}
		int asd = WinCheck();
		myChoiceScore += asd;
		return;

	}
	if (mySquare[largestIndex].myUp == false)
	{
		mySquare[largestIndex].myUp = true;
		CU::Vector2i pos = mySquare[largestIndex].myPosition + CU::Vector2i(0, -1);
		int i = FindIndex(pos.x, pos.y);
		if (i != -1)
		{
			mySquare[i].myDown = true;
		}
		int asd = WinCheck();
		myChoiceScore += asd;
		return;

	}
	if (mySquare[largestIndex].myLeft == false)
	{
		mySquare[largestIndex].myLeft = true;

		CU::Vector2i pos = mySquare[largestIndex].myPosition + CU::Vector2i(-1, 0);
		int i = FindIndex(pos.x, pos.y);
		if (i != -1)
		{
			mySquare[i].myRight = true;
		}


		int asd = WinCheck();
		myChoiceScore += asd;
		return;

	}
	if (mySquare[largestIndex].myRight == false)
	{
		mySquare[largestIndex].myRight = true;
		CU::Vector2i pos = mySquare[largestIndex].myPosition + CU::Vector2i(1, 0);
		int i = FindIndex(pos.x, pos.y);
		if (i != -1)
		{
			mySquare[i].myLeft = true;
		}

		int asd = WinCheck();
		myChoiceScore += asd;
		return;
	}
}

int Game::CountTaken(int aIndex)
{
	int count = 0;
	if (mySquare[aIndex].myDown == true)
	{
		count++;
	}
	if (mySquare[aIndex].myUp == true)
	{
		count++;
	}
	if (mySquare[aIndex].myLeft == true)
	{
		count++;
	}
	if (mySquare[aIndex].myRight == true)
	{
		count++;
	}
	return count;
}


int Game::FindIndex(int aX, int aY)
{
	for (int i = 0; i < mySquare.Size(); i++)
	{
		if (mySquare[i].myPosition.x == aX &&  mySquare[i].myPosition.y == aY)
		{
			return i;
		}
	}
	return -1;
}

bool Game::CheckIfLineExists(CU::Vector2i aPosition, int aIndex)
{
	bool lineExists = false;
	int index = FindIndex(aPosition.x, aPosition.y);
	if (index != -1)
	{
		switch (aIndex)
		{
		case 0:
			return mySquare[index].myUp;
			break;
		case 1:
			return mySquare[index].myLeft;
			break;
		case 2:
			return mySquare[index].myDown;
			break;
		case 3:
			return mySquare[index].myRight;
			break;
		default:
			break;
		}
	}
}

int Game::WinCheck()
{
	int result = 0;
	for (int i = 0; i < mySquare.Size(); i++)
	{
		if (mySquare[i].myRight == true && mySquare[i].myLeft == true && mySquare[i].myUp == true && mySquare[i].myDown == true && mySquare[i].myIsTaken == false)
		{
			mySquare[i].myIsTaken = true;
			result++;
		}
	}
	return result;
}



void Game::HandleInputWithoutGUI()
{
}

void Game::Notify(const eTriggerType& aTriggerType, void* aTrigger)
{
}

void Game::Render()
{
	SpriteRenderCommand* renderNode = nullptr;
	for (int i = 0; i < mySquare.Size(); i++)
	{
		renderNode = new SpriteRenderCommand(myNodeSprite, CU::Vector2f((mySquare[i].myPosition.x * 100.f) + 200, (mySquare[i].myPosition.y * 100.f) + 100.f));
		renderNode->SetZ(0.9f);
		Megaton::GetRenderManager()->AddCommand(renderNode);
		renderNode = new SpriteRenderCommand(myNodeSprite, CU::Vector2f((mySquare[i].myPosition.x * 100.f) + 300, (mySquare[i].myPosition.y  * 100.f) + 100.f));
		renderNode->SetZ(0.9f);
		Megaton::GetRenderManager()->AddCommand(renderNode);
		renderNode = new SpriteRenderCommand(myNodeSprite, CU::Vector2f((mySquare[i].myPosition.x * 100.f) + 200, (mySquare[i].myPosition.y  * 100.f) + 200.f));
		renderNode->SetZ(0.9f);
		Megaton::GetRenderManager()->AddCommand(renderNode);
		renderNode = new SpriteRenderCommand(myNodeSprite, CU::Vector2f((mySquare[i].myPosition.x * 100.f) + 300, (mySquare[i].myPosition.y  * 100.f) + 200.f));
		renderNode->SetZ(0.9f);
		Megaton::GetRenderManager()->AddCommand(renderNode);

		if (mySquare[i].myLeft == true)
		{
			renderNode = new SpriteRenderCommand(myHoriSprite, CU::Vector2f((mySquare[i].myPosition.x * 100.f) + 200, (mySquare[i].myPosition.y* 100.f) + 100.f));

			renderNode->SetZ(0.5);
			Megaton::GetRenderManager()->AddCommand(renderNode);

		}

		if (mySquare[i].myRight == true)
		{
			renderNode = new SpriteRenderCommand(myHoriSprite, CU::Vector2f((mySquare[i].myPosition.x * 100.f) + 300, (mySquare[i].myPosition.y * 100.f) + 100.f));
			renderNode->SetZ(0.5);

			Megaton::GetRenderManager()->AddCommand(renderNode);

		}

		if (mySquare[i].myUp == true)
		{
			renderNode = new SpriteRenderCommand(myVertSprite, CU::Vector2f((mySquare[i].myPosition.x * 100.f) + 200, (mySquare[i].myPosition.y * 100.f) + 100.f));
			renderNode->SetZ(0.5);
			Megaton::GetRenderManager()->AddCommand(renderNode);
		}

		if (mySquare[i].myDown == true)
		{
			renderNode = new SpriteRenderCommand(myVertSprite, CU::Vector2f((mySquare[i].myPosition.x * 100.f) + 200, (mySquare[i].myPosition.y * 100.f) + 200.f));
			renderNode->SetZ(0.5);
			Megaton::GetRenderManager()->AddCommand(renderNode);

		}


		if (mySquare[i].myIsTaken)
		{
			renderNode = new SpriteRenderCommand(myCubeSprite, CU::Vector2f((mySquare[i].myPosition.x * 100.f) + 200, (mySquare[i].myPosition.y * 100.f) + 100.f));
			renderNode->SetZ(0.5);
			Megaton::GetRenderManager()->AddCommand(renderNode);

			//RenderSquare continue

			//continue;
		}

	}
	std::string mad;
	std::string mad2;
	mad = std::string("AI : " + std::to_string(myChoiceScore));
	mad2 = std::string("Random : " + std::to_string(myRandomScore));
	FontRenderCommand* font1 = new FontRenderCommand(mad, Megaton::GetResourceManager()->GetFont(), CU::Vector2f(200, 10));
	FontRenderCommand* font2 = new FontRenderCommand(mad2, Megaton::GetResourceManager()->GetFont(), CU::Vector2f(600, 10));
	font1->SetColor(ARGB(200, 0, 0, 0));
	font2->SetColor(ARGB(200, 0, 0, 0));
	Megaton::GetRenderManager()->AddCommand(font1);
	Megaton::GetRenderManager()->AddCommand(font2);

}