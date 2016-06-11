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
	myNodeSprite = Megaton::GetResourceManager()->GetSprite("Data/node.png");
	myVertSprite = Megaton::GetResourceManager()->GetSprite("Data/nodeHori.png");
	myHoriSprite = Megaton::GetResourceManager()->GetSprite("Data/nodeLong.png");
	myCubeSprite = Megaton::GetResourceManager()->GetSprite("Data/nodeCube.png");

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



}