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
	
	myBoundingBox.SetWidth(mySprite->GetWidth());
	myBoundingBox.SetHeight(mySprite->GetHeight());
}

void Avatar::HandleInput()
{
	
}

void Avatar::HandleCollision(CU::GrowingArray<FloorTile> tiles)
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

AABB Avatar::GetAABB()
{
	myBoundingBox.SetX(myPosition.x);
	myBoundingBox.SetY(myPosition.y);

	return myBoundingBox;
}



