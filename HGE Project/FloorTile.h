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
	AABB GetAABB() const;

	void Render();
	void Recalculate(int tileHeight);

	int GetTileHeight();
private:
	hgeSprite* myFloorSprite;
	AABB myBoundingBox;

	int myTileHeight;

};

