#include "stdafx.h"
#include "Avatar.h"
#include "Megaton.h"
#include "Renderer/SpriteRenderCommand.h"
#include "Defines.h"


Avatar::Avatar()
{
	mySprite = nullptr;
	myPosition.Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 5*4);
	myFloorPlacing = myPosition.myY;
	myMovementSpeed = 200.f;

}


Avatar::~Avatar()
{
}

void Avatar::Init()
{
	mySprite = Megaton::GetResourceManager()->GetSprite("Data/player.png");
}

void Avatar::HandleInput()
{

	float deltaTime = 1 / Megaton::GetTimerManager()->GetFPS();

	myNewPosition = myPosition;
	if (Megaton::GetInputManager()->ButtonIsDown(eButton::eA))
	{
		myNewPosition += CU::Vector2f(-1, 0) * myMovementSpeed*deltaTime;
	}
	if (Megaton::GetInputManager()->ButtonIsDown(eButton::eD))
	{
		myNewPosition += CU::Vector2f(1, 0) *myMovementSpeed*deltaTime;
	}
	if (Megaton::GetInputManager()->ButtonPressed(eButton::eSPACE))
	{
		//if (myFloorPlacing <= myPosition.myY)
		{
			myVelocity = CU::Vector2f(0, -1) * 300.f;
		}
	}


}

void Avatar::Render()
{
	SpriteRenderCommand* spriteRenderCommand = new SpriteRenderCommand(mySprite, myPosition);
	Megaton::GetRenderManager()->AddCommand(spriteRenderCommand);
}

void Avatar::Update()
{
	HandleInput();

	float deltaTime = 1 / Megaton::GetTimerManager()->GetFPS();
	myNewPosition += myVelocity * deltaTime;
	if (myNewPosition.myY >= myFloorPlacing)
	{
        myVelocity.myY = 0.f;
	}
	else
	{
		if (myVelocity.myY != 0.f)
		{
			myVelocity += CU::Vector2f(0, 1000.f) *deltaTime;

		}
	}
	myPosition = myNewPosition;
	Megaton::GetTimerManager()->GetFrameTime();
}


