#pragma once
#include "CommonUtilities\Vector2.h"
#include "CommonUtilities\AABB.h"
#include "Camera.h"

class SpriteRenderCommand;
class hgeSprite;

class FloorTile
{
public:
	FloorTile();
	~FloorTile();
	
	CU::Vector2f myPosition;

	void Render(Camera& aCamera);
	void Recalculate(int tileHeight);

	int GetTileHeight();
private:
	hgeSprite* myFloorSprite;
	AABB myBoundingBox;

	int myTileHeight;

};

