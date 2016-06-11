#pragma once
#include "ResourceManager.h"
#include "CommonUtilities/Vector.h"
#include "Camera.h"
class Avatar
{
public:
	Avatar();
	~Avatar();

	void Init();
	void Render(Camera& myCamera);
	void Update();
	void HandleInput();

	CU::Vector2f myPosition;
private:
	CU::Vector2f myNewPosition;

	CU::Vector2f myVelocity;
	float myMovementSpeed;
	float myFloorPlacing;

	hgeSprite* mySprite;
};

