#include "stdafx.h"
#include "Avatar.h"
#include "Megaton.h"
#include "Renderer/SpriteRenderCommand.h"
#include "Defines.h"
#include <algorithm>


Avatar::Avatar()
{
	mySprite = nullptr;
	myPosition.Set(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 5 * 4);
	myFloorPlacing = WINDOW_HEIGHT;
	myMovementSpeed = 100.f;
	myIsDucked = false;
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
	float deltaTime = 1 / Megaton::GetTimerManager()->GetFPS();

	myNewPosition = myPosition;
	if (Megaton::GetInputManager()->ButtonIsDown(eButton::eA))
	{
		if (CollidedLastFrame == false)
		{
			myNewPosition += CU::Vector2f(-1.f, 0) * myMovementSpeed*deltaTime;

		}
		else
		{
			myNewPosition += CU::Vector2f(-1, 0) * myMovementSpeed*deltaTime;

		}
	}

	if (Megaton::GetInputManager()->ButtonIsDown(eButton::eD))
	{
		if (CollidedLastFrame == false)
		{
			myNewPosition += CU::Vector2f(1.f, 0) *myMovementSpeed*deltaTime;
		}
		else
		{
			myNewPosition += CU::Vector2f(1, 0) *myMovementSpeed*deltaTime;

		}
	}

	if (Megaton::GetInputManager()->ButtonIsDown(eButton::eSPACE))
	{
		if (/*CollidedLastFrame == true && */myVelocity.y == 0.f)
		{
			myVelocity = CU::Vector2f(0, -1) * 240.f;
		}
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
		myNewPosition.y += AVATAR_HEIGHT / 2;

		mySprite->SetTextureRect(0, 0, AVATAR_WIDTH, AVATAR_HEIGHT / 2);
	}
	else
	{
		if (myIsDucked)
		{
			myNewPosition.y -= AVATAR_HEIGHT / 2;
			myNewPosition.y--;
		}

		mySprite->SetTextureRect(0, 0, AVATAR_WIDTH, AVATAR_HEIGHT);

	}

	myIsDucked = shouldDuck;
}

CU::Vector2f Avatar::HandleCollision(CU::GrowingArray<FloorTile> tiles, CU::Vector2f position)
{
	auto boundBox = GetAABB();
	bool upperleftBlocked = false;
	bool upperRightBlocked = false;
	bool lowerLeftBlocked = false;
	bool lowerRightBlocked = false;
	bool upBlocked = false;
	bool rightBlocked = false;
	bool leftBlocked = false;
	bool downBlocked = false;
	CollidedLastFrame = false;

	AABB aabb = AABB(position.x, position.y, boundBox.GetWidth(), boundBox.GetHeight());

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

	if (upperleftBlocked && leftBlocked || lowerLeftBlocked && leftBlocked)
	{
		position.x = max(position.x, myPosition.x);
		CollidedLastFrame = true;
	}

	if (upperRightBlocked && rightBlocked || lowerRightBlocked && rightBlocked)
	{
		position.x = min(position.x, myPosition.x);
		CollidedLastFrame = true;

	}

	if (upperleftBlocked && upBlocked || upperRightBlocked && upBlocked)
	{
		position.y = max(position.y, myPosition.y);
		CollidedLastFrame = true;

	}

	if (lowerLeftBlocked && downBlocked || lowerRightBlocked && downBlocked)
	{
		position.y = min(position.y, myPosition.y);
		CollidedLastFrame = true;

		myVelocity.y = min(myVelocity.y, 0);
	}

	return position;
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
	myNewPosition += myVelocity * deltaTime;

	if (myNewPosition.y >= myFloorPlacing)
	{
		myVelocity.y;
	}
	//if ()
	{
		myVelocity += CU::Vector2f(0, 1000.f) * deltaTime;
	}

	myNewPosition = HandleCollision(tiles, myNewPosition);
	myPosition = myNewPosition;

	Megaton::GetTimerManager()->GetFrameTime();
}

AABB Avatar::GetAABB()
{
	auto boundingBox = AABB(myPosition.x, myPosition.y, mySprite->GetWidth(), mySprite->GetHeight());

	return boundingBox;
}
