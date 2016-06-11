#include "stdafx.h"
#include "GameState.h"
#include "Megaton.h"

GameState::GameState(void)
{
	mySubStates.Init(4);
	myWidgets.Init(16);
}

GameState::~GameState(void) { }

void GameState::Init()
{
}
void GameState::Update()
{
	if(Megaton::GetGUIManager()->HasWidgetFocus() == false)
	{
		HandleInput();
	}
	HandleInputWithoutGUI();

}