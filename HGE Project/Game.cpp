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
	SpriteRenderCommand* spriteRenderCommand = new SpriteRenderCommand(myFloorSprite, CU::Vector2f(10.0f, 10.0f));
	Megaton::GetRenderManager()->AddCommand(spriteRenderCommand);

}