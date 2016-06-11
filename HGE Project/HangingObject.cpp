#include "stdafx.h"
#include "HangingObject.h"
#include "SpriteRenderCommand.h"
#include "Megaton.h"
#include "hgesprite.h"
#include "Defines.h"

HangingObject::HangingObject()
{
	mySprite = Megaton::GetResourceManager()->GetSprite("Data/bullet.png");
}

HangingObject::~HangingObject()
{
}

void HangingObject::Render(Camera& aCamera)
{
	Megaton::GetRenderManager()->AddCommand(new SpriteRenderCommand(mySprite, aCamera.ConvertPositionToCameraPosition(myPosition)));
}

AABB HangingObject::GetAABB() const
{
	return myBoundingBox;
}


CU::Vector2f HangingObject::GetPostion() const
{
	return myPosition;
}

void HangingObject::SetPosition(const CU::Vector2f& newPosition)
{
	myPosition = newPosition;
	myBoundingBox = AABB(myPosition.x, myPosition.y, mySprite->GetWidth(), mySprite->GetHeight());
}