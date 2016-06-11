#include "stdafx.h"
#include "Avatar.h"
#include "Megaton.h"
#include "Renderer/SpriteRenderCommand.h"
#include "Defines.h"
#include <algorithm>


Avatar::Avatar()
{
	mySprite = nullptr;
	myPosition.Set(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 5);
	myFloorPlacing = WINDOW_HEIGHT;
	myMovementSpeed = 100.f;
	myGravity.Set(0, 0);
}


Avatar::~Avatar()
{
}

void Avatar::Init()
{
	mySprite = Megaton::GetResourceManager()->GetSprite("Data/playerAvatar.png");

	SetDuckedState(false);
}

void Avatar::HandleInput()
{
	myVelocity.Set(0, 0);

	if (Megaton::GetInputManager()->ButtonIsDown(eButton::eA))
	{
		myVelocity.x = -myMovementSpeed;
	}

	if (Megaton::GetInputManager()->ButtonIsDown(eButton::eD))
	{
		myVelocity.x = myMovementSpeed;
	}

	if (Megaton::GetInputManager()->ButtonIsDown(eButton::eSPACE))
	{
		myVelocity.y = -240.f;
	}

	if (Megaton::GetInputManager()->ButtonPressed(eButton::eS))
		SetDuckedState(true);

	if (Megaton::GetInputManager()->ButtonReleased(eButton::eS))
		SetDuckedState(false);
}

void Avatar::SetDuckedState(bool shouldDuck)
{
	if (shouldDuck)
	{
		if (mySize.y == AVATAR_HEIGHT) // check if we need to actually duck 
		{
			myPosition.y += AVATAR_HEIGHT / 2;
			mySize.y = AVATAR_HEIGHT / 2;
		}
	}
	else
	{
		if (mySize.y != AVATAR_HEIGHT)// check if we need to get up again

		{
			myPosition.y -= AVATAR_HEIGHT / 2;
			mySize.y = AVATAR_HEIGHT;
		}
	}
}

CU::Vector2f Avatar::HandleCollision(CU::GrowingArray<FloorTile> tiles, CU::Vector2f movement)
{
	auto leftAABB = GetAABB();
	auto upAABB = GetAABB();
	auto rightAABB = GetAABB();

	aabb.SetX(myPosition.x + movement.x);
	aabb.SetY(myPosition.y + movement.y);


	bool upBlocked = false;
	bool rightBlocked = false;
	bool leftBlocked = false;
	bool downBlocked = false;

	CU::Vector2f upperLeft = CU::Vector2f(aabb.GetX(), aabb.GetY());
	CU::Vector2f up = CU::Vector2f(aabb.GetX(), aabb.GetY() + aabb.GetWidth() / 2);
	CU::Vector2f upperRight = CU::Vector2f(aabb.GetX() + aabb.GetWidth(), aabb.GetY());
	CU::Vector2f right = CU::Vector2f(aabb.GetX() + aabb.GetWidth(), aabb.GetY() + aabb.GetHeight() / 2);
	CU::Vector2f lowerLeft = CU::Vector2f(aabb.GetX(), aabb.GetY() + aabb.GetHeight());
	CU::Vector2f left = CU::Vector2f(aabb.GetX(), aabb.GetY() + aabb.GetHeight() / 2);
	CU::Vector2f lowerRight = CU::Vector2f(aabb.GetX() + aabb.GetWidth(), aabb.GetY() + aabb.GetHeight());
	CU::Vector2f low = CU::Vector2f(aabb.GetX() + aabb.GetWidth() / 2, aabb.GetY() + aabb.GetHeight());

	auto tileCount = tiles.Count();
	for (auto tileIndex = 0; tileIndex < tileCount; tileIndex++)
	{
		auto tileAABB = tiles[tileIndex].GetAABB();

		if (tileAABB.Inside(upperLeft))
		{
			upperleftBlocked = true;
		}

		if (tileAABB.Inside(upperRight))
		{
			upperRightBlocked = true;
		}

		if (tileAABB.Inside(lowerLeft))
		{
			lowerLeftBlocked = true;
		}

		if (tileAABB.Inside(lowerRight))
		{
			lowerRightBlocked = true;
		}
		if (tileAABB.Inside(up))
		{
			upBlocked = true;
		}
		if (tileAABB.Inside(low))
		{
			downBlocked = true;
		}
		if (tileAABB.Inside(left))
		{
			leftBlocked = true;
		}
		if (tileAABB.Inside(right))
		{
			rightBlocked = true;
		}
	}

	if (upperleftBlocked || leftBlocked || lowerLeftBlocked)
		movement.x = max(movement.x, 0);

	if (upperRightBlocked || rightBlocked || lowerRightBlocked)
		movement.x = min(movement.x, 0);

	if (upperleftBlocked || upBlocked || upperRightBlocked)
		movement.y = max(movement.y, 0);

	if (lowerLeftBlocked || downBlocked || lowerRightBlocked)
	{
		movement.y = min(movement.y, 0);
		myGravity.Set(0, 0);
	}

	return movement;
}

CU::Vector2f Avatar::GetPosition() const
{
	return myPosition;
}

void Avatar::Render(Camera& aCamera) const
{
	SpriteRenderCommand* spriteRenderCommand = new SpriteRenderCommand(mySprite, aCamera.ConvertPositionToCameraPosition(myPosition));
	Megaton::GetRenderManager()->AddCommand(spriteRenderCommand);
}

void Avatar::Update(CU::GrowingArray<FloorTile> tiles)
{
	HandleInput();

	float deltaTime = 1 / Megaton::GetTimerManager()->GetFPS();

	myGravity.y = 1000.f * deltaTime;
	auto movement = myVelocity * deltaTime;
	movement += myGravity;


	if (myPosition.y + movement.y > WINDOW_HEIGHT)
	{
		movement.y = min(0, movement.y);
		myGravity.Set(0, 0);
	}

	movement = HandleCollision(tiles, movement);
	myPosition += movement;
}

AABB Avatar::GetAABB() const
{
	auto boundingBox = AABB(myPosition.x, myPosition.y, mySprite->GetWidth(), mySprite->GetHeight());

	return boundingBox;
}
