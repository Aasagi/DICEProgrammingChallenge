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
	
	AABB GetAABB() const;

	void Render(Camera& aCamera);
	void Recalculate(int tileHeight);
	CU::Vector2f GetPosition() const;
	void SetPosition(CU::Vector2f aPosition);

	int GetTileHeight();
private:
	CU::Vector2f myPosition;
	hgeSprite* myFloorSprite;
	AABB myBoundingBox;

	int myTileHeight;

};

