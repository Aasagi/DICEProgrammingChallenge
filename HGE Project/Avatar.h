#pragma once
#include "ResourceManager.h"
#include "CommonUtilities/Vector.h"
#include "CommonUtilities/GrowingArray.h"
#include "FloorTile.h"

class Avatar
{
public:
	Avatar();
	~Avatar();

	void Init();
	void Render();
	void Update();
	void HandleInput();
	void HandleCollision(CU::GrowingArray<FloorTile> tiles);
	AABB GetAABB();

private:
	CU::Vector2f myPosition;
	AABB myBoundingBox;

	hgeSprite* mySprite;
};

