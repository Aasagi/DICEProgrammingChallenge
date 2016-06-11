#include "stdafx.h"
#include <thread>
#include "GameLoop.h"
#include "Renderer\Renderer.h"
#include "Megaton.h"

//-------------------GameStates----------------//
#include "Game.h"
#include "MainMenu.h"
//-------------------GameStates----------------//

GameLoop::GameLoop(void)
{
	myGameIsRunning = true;
	myGameIsLoaded = false;
}

GameLoop::~GameLoop(void)
{
	Megaton::Destroy();
}

void GameLoop::Init(HGE* aHGE, const CU::Vector2i& aResolution)
{
	myHGE = aHGE;

	myRenderer.Init(myHGE);
	myRenderThread = new std::thread(&Renderer::ThreadedUpdate, &myRenderer);
	Megaton::Create(myHGE, &myRenderer, aResolution);
}

bool GameLoop::ReadHgeMSG()
{
	if(PeekMessage(&myWindowMessage, nullptr, 0, 0, PM_REMOVE))
	{
		if (myWindowMessage.message == WM_QUIT)
		{
			myGameIsRunning = false;
			return true;
		}
		TranslateMessage(&myWindowMessage);
		DispatchMessage(&myWindowMessage);
	}
	return false;
}

void GameLoop::Run()
{
	Megaton::GetTriggerManager()->AddObserver(eTriggerType::eQuitGame, this);
	Megaton::GetTriggerManager()->AddObserver(eTriggerType::ePushMainState, this);
	Megaton::GetTriggerManager()->AddObserver(eTriggerType::ePopMainState, this);
	Megaton::GetTriggerManager()->AddObserver(eTriggerType::ePushSubState, this);
	Megaton::GetTriggerManager()->AddObserver(eTriggerType::ePopSubState, this);

	myGame = new Game();
	myGame->Init();

	myStateStack.Push(myGame);

	//GameState* game = new MainMenu();
	//game->Init();
	//myStateStack.Push(game);

	while (myGameIsRunning == true)
	{
		if(ReadHgeMSG() == false)
		{
			//SetCapture(myHGE->System_GetState(HGE_HWND));
			if (Megaton::GetInputManager()->ButtonIsDown(eButton::eESCAPE) == true)
			{
				myGameIsRunning = false;
				break;
			}
			Update();
		}
	}
	myRenderer.ShutDown();
	myRenderThread->join();
	delete myRenderThread;
}

void GameLoop::Update()
{
	Megaton::Update(myStateStack.Top());

	if(myStateStack.Size() > 0)
	{
		myStateStack.Top()->Update();
	}
}

void GameLoop::Notify(const eTriggerType& aTriggerType, void* aTrigger)
{
	Trigger* trigger = reinterpret_cast<Trigger*>(aTrigger);
	switch(aTriggerType)
	{
	case eTriggerType::eQuitGame:
		while(myStateStack.Size() > 0)
		{
			myStateStack.Pop();
		}
		myGameIsRunning = false;
		break;
		//-------------------------------MAIN STATES LOGIC-------------------------------//
	case eTriggerType::ePushMainState:
		myStateStack.Push(trigger->myGameState);
		break;

	case eTriggerType::ePopMainState:
		myStateStack.Pop();
		if(myStateStack.Size() <= 0)
		{
			myGameIsRunning = false;
		}
		break;
		//-------------------------------MAIN STATES LOGIC-------------------------------//

		//-------------------------------SUB STATES LOGIC-------------------------------//
	case eTriggerType::ePushSubState:
		myStateStack.Top()->PushGameState(trigger->myGameState);
		break;

	case eTriggerType::ePopSubState:
		myStateStack.Top()->PopGameState();
		break;
		//-------------------------------SUB STATES LOGIC-------------------------------//
	}
}