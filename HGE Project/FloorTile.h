#pragma once
#include "CommonUtilities\Vector2.h"
#include "CommonUtilities\AABB.h"

class SpriteRenderCommand;
class hgeSprite;

class FloorTile
{
public:
	FloorTile();
	~FloorTile();
	
	CU::Vector2f myPosition;

	SpriteRenderCommand* GetRenderCommand();
private:
	hgeSprite* myFloorSprite;
	AABB myBoundingBox;

	int myTileHeight;

};

