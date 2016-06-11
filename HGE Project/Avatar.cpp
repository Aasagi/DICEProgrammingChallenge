#include "stdafx.h"
#include "Avatar.h"
#include "Megaton.h"
#include "Renderer/SpriteRenderCommand.h"


Avatar::Avatar()
{
	mySprite = nullptr;
	myPosition.Set(0, 0);
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
	SpriteRenderCommand* spriteRenderCommand = new SpriteRenderCommand(mySprite, CU::Vector2f(10.0f, 10.0f));
	Megaton::GetRenderManager()->AddCommand(spriteRenderCommand);	

}

void Avatar::Update()
{
	
}


