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
	bool GetHeadIsColliding();
	AABB GetAABB();
	CU::Vector2f GetPosition() const;

	CU::Vector2f myPosition;
private:
	CU::Vector2f HandleCollision(CU::GrowingArray<FloorTile> tiles, CU::Vector2f position);

	CU::Vector2f myNewPosition;

	CU::Vector2f myVelocity;
	float myMovementSpeed;
	float myFloorPlacing;
	bool CollidedLastFrame;
	hgeSprite* mySprite;
	bool myIsDucked;
	bool myIsCollidingWithHead;
};

