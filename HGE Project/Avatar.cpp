#include "stdafx.h"
#include "Avatar.h"
#include "Megaton.h"
#include "Renderer/SpriteRenderCommand.h"
#include "Defines.h"


Avatar::Avatar()
{
	mySprite = nullptr;
	myPosition.Set(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
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
	
}

void Avatar::Render()
{
	SpriteRenderCommand* spriteRenderCommand = new SpriteRenderCommand(mySprite, myPosition);
	Megaton::GetRenderManager()->AddCommand(spriteRenderCommand);	
}

void Avatar::Update()
{
	
}


