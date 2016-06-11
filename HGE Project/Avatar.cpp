#include "stdafx.h"
#include "Avatar.h"
#include "Megaton.h"
#include "Renderer/SpriteRenderCommand.h"
#include "Defines.h"
#include <algorithm>


Avatar::Avatar()
{
	mySprite = nullptr;
	myPosition.Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 5 * 4);
	myFloorPlacing = myPosition.myY;
	myMovementSpeed = 200.f;

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

CU::Vector2f Avatar::HandleCollision(CU::GrowingArray<FloorTile> tiles, CU::Vector2f position)
{
	bool zeroLeft = false;
	bool zeroRight = false; 
	bool zeroUp = false; 
	bool zeroDown = false;
	
	AABB aabb = AABB(position.x, position.y, myBoundingBox.GetWidth(), myBoundingBox.GetHeight());

	CU::Vector2f upperLeft = CU::Vector2f(aabb.GetX(), aabb.GetY());
	CU::Vector2f upperRight = CU::Vector2f(aabb.GetX() + aabb.GetWidth(), aabb.GetY());
	CU::Vector2f lowerLeft = CU::Vector2f(aabb.GetX(), aabb.GetY() + aabb.GetHeight());
	CU::Vector2f lowerRight = CU::Vector2f(aabb.GetX() + aabb.GetWidth(), aabb.GetY() + aabb.GetHeight());

	auto tileCount = tiles.Count();
	for (auto tileIndex = 0; tileIndex < tileCount; tileIndex++)
	{
		auto tileAABB = tiles[tileIndex].GetAABB();
		
		if (tileAABB.Inside(upperLeft) || tileAABB.Inside(lowerLeft))
			zeroLeft = true;

		if (tileAABB.Inside(upperLeft) || tileAABB.Inside(upperRight))
			zeroUp = true;

		if (tileAABB.Inside(upperRight) || tileAABB.Inside(lowerRight))
			zeroRight = true;

		if (tileAABB.Inside(upperRight) || tileAABB.Inside(lowerRight))
			zeroDown = true;
	}

	if (zeroLeft)
		position.x = max(position.x, 0);

	if (zeroRight)
		position.x = min(position.x, 0);

	if (zeroUp)
		position.y = max(position.y, 0);

	if (zeroDown)
		position.y = min(position.y, 0);

	return position;
}


void Avatar::Render(Camera& aCamera)
{
	SpriteRenderCommand* spriteRenderCommand = new SpriteRenderCommand(mySprite, aCamera.ConvertPositionToCameraPosition(myPosition));
	Megaton::GetRenderManager()->AddCommand(spriteRenderCommand);
}

void Avatar::Update(CU::GrowingArray<FloorTile> tiles)
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

	myNewPosition = HandleCollision(tiles, myNewPosition);
	myPosition = myNewPosition;

	Megaton::GetTimerManager()->GetFrameTime();
}

AABB Avatar::GetAABB()
{
	myBoundingBox.SetX(myPosition.x);
	myBoundingBox.SetY(myPosition.y);

	return myBoundingBox;
}



