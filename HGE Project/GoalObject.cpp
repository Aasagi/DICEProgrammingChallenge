#include "stdafx.h"
#include "GoalObject.h"
#include "SpriteRenderCommand.h"
#include "Megaton.h"
#include "hgesprite.h"
#include "Defines.h"

GoalObject::GoalObject()
{
	myGoalSprite = Megaton::GetResourceManager()->GetSprite("Data/goal.png");
}

GoalObject::~GoalObject()
{
}

void GoalObject::Render(Camera& aCamera)
{
	Megaton::GetRenderManager()->AddCommand(new SpriteRenderCommand(myGoalSprite, aCamera.ConvertPositionToCameraPosition(myPosition - CU::Vector2f(0.0f, myGoalSprite->GetHeight() * 0.5f))));
}

AABB GoalObject::GetAABB() const
{
	return myBoundingBox;
}


CU::Vector2f GoalObject::GetPostion() const
{
	return myPosition;
}

void GoalObject::SetPosition(const CU::Vector2f& newPosition)
{
	myPosition = newPosition;
	myBoundingBox = AABB(myPosition.x, myPosition.y, myGoalSprite->GetWidth(), myGoalSprite->GetHeight());
}