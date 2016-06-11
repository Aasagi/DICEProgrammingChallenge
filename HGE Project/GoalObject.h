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

	AABB GetAABB() const;
	CU::Vector2f GetPostion() const;
	void SetPosition(const CU::Vector2f& newPosition);

	void Render(Camera& aCamera);

private:
	hgeSprite* myGoalSprite;
	AABB myBoundingBox;
	CU::Vector2f myPosition;
};

