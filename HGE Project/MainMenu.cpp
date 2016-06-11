#include "stdafx.h"
#include "MainMenu.h"
#include "hgesprite.h"
#include "Renderer\SpriteRenderCommand.h"
#include "Megaton.h"
#include "GUI/Button.h"

//--------------------GAME STATES ---------------------//
#include "Game.h"
//--------------------GAME STATES ---------------------//

MainMenu::MainMenu(void)
{
}

MainMenu::~MainMenu(void)
{

}

void MainMenu::Init()
{
	//------------------------------LENNY CODE-------------------------------//
	CU::Vector2f scaling = Megaton::GetSettings()->myWindowResolution / CU::Vector2f(1920, 1080);

#pragma region CREATE START GAME BUTTON
	Button* gameButton = new Button();
	gameButton->Init();
	gameButton->AddSprite(eWidgetState::eNormal, Megaton::GetResourceManager()->GetSprite("Data/startButton.png"));
	gameButton->AddSprite(eWidgetState::eHover, Megaton::GetResourceManager()->GetSprite("Data/startButtonHover.png"));
	gameButton->AddSprite(eWidgetState::eOnPressed, Megaton::GetResourceManager()->GetSprite("Data/startButtonOnPressed.png"));

	gameButton->SetPosition(CU::Vector2f(832, 200) * scaling);
	gameButton->SetAABB(AABB(0,0,256,64));
	gameButton->SetSpriteState(eWidgetState::eNormal);
	gameButton->SetZ(-1.f);

	std::function<void()> gameClick = [this]()
	{
		Trigger* newTrigger = new Trigger();
		newTrigger->myGameState = new Game();
		newTrigger->myGameState->Init();
		Megaton::GetTriggerManager()->RecieveMsg(eTriggerType::ePushMainState, newTrigger);
	};

	gameButton->AddWidgetEvent(eGUIEvent::eMouseClick, gameClick);
	myWidgets.Add(gameButton);
	
#pragma endregion
#pragma region CREATE EXIT GAME BUTTON
	Button* exitButton = new Button();
	exitButton->Init();
	exitButton->AddSprite(eWidgetState::eNormal, Megaton::GetResourceManager()->GetSprite("Data/exitButton.png"));
	exitButton->AddSprite(eWidgetState::eHover, Megaton::GetResourceManager()->GetSprite("Data/exitButtonHover.png"));
	exitButton->AddSprite(eWidgetState::eOnPressed, Megaton::GetResourceManager()->GetSprite("Data/exitButtonOnPressed.png"));

	exitButton->SetPosition(CU::Vector2f(832, 400) * scaling);
	exitButton->SetAABB(AABB(0, 0, 256, 64));
	exitButton->SetSpriteState(eWidgetState::eNormal);
	exitButton->SetZ(-1.f);

	std::function<void()> exitClick = []()
	{
		Megaton::GetTriggerManager()->RecieveMsg(eTriggerType::eQuitGame, nullptr);
	};

	exitButton->AddWidgetEvent(eGUIEvent::eMouseClick, exitClick);
	myWidgets.Add(exitButton);
	
#pragma endregion
	
	//------------------------------LENNY CODE-------------------------------//
}

void MainMenu::Update()
{
	/*CU::Stack<GameState*> activeGameStates = mySubStates;
	while(activeGameStates.Size() > 0)
	{
		activeGameStates.Pop()->Update();
	}*/
	
	if (myMusic.IsPlaying() == false)
	{
		myMusic.Play();
	}

	for(int i = mySubStates.Size() - 1; 0 <= i; --i)
	{
		mySubStates[i]->Update();
	}

	GameState::Update();
}

void MainMenu::HandleInput()
{
}

void MainMenu::HandleInputWithoutGUI()
{
}