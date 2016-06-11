#pragma once
#include "CommonUtilities\Vector2.h"
#include "CommonUtilities\AABB.h"
#include "Camera.h"

class SpriteRenderCommand;
class hgeSprite;

class GoalObject
{
public:
	GoalObject();
	~GoalObject();

	CU::Vector2f myPosition;
	AABB GetAABB() const;

	void Render(Camera& aCamera);

	int GetTileHeight();
private:
	hgeSprite* myGoalSprite;
	AABB myBoundingBox;
};

