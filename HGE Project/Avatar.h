#pragma once
#include "ResourceManager.h"
#include "CommonUtilities/Vector.h"
#include "Camera.h"
#include "CommonUtilities/GrowingArray.h"
#include "FloorTile.h"

class Avatar
{
public:
	Avatar();
	~Avatar();

	void Init();
	void Render(Camera& myCamera) const;
	void Update(CU::GrowingArray<FloorTile> tiles);
	void HandleInput();
	void SetDuckedState(bool);
	AABB GetAABB() const;
	CU::Vector2f GetPosition() const;

private:
	CU::Vector2f HandleCollision(CU::GrowingArray<FloorTile> tiles, CU::Vector2f position);
	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	CU::Vector2f myGravity;
	CU::Vector2f mySize;
	float myMovementSpeed;
	float myFloorPlacing;
	hgeSprite* mySprite;
};

