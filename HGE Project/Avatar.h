#pragma once
#include "ResourceManager.h"
#include "CommonUtilities/Vector.h"

class Avatar
{
public:
	Avatar();
	~Avatar();

	void Init();
	void Render();
	void Update();
	void HandleInput();

private:
	CU::Vector2f myPosition;
	CU::Vector2f myNewPosition;

	CU::Vector2f myVelocity;
	float myMovementSpeed;
	float myFloorPlacing;

	hgeSprite* mySprite;
};

