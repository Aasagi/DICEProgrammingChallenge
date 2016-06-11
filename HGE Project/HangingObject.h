#pragma once
#include "CommonUtilities\Vector2.h"
#include "CommonUtilities\AABB.h"
#include "Camera.h"

class SpriteRenderCommand;
class hgeSprite;

class HangingObject
{
public:
	HangingObject();
	~HangingObject();

	AABB GetAABB() const;
	CU::Vector2f GetPostion() const;
	void SetPosition(const CU::Vector2f& newPosition);

	void Render(Camera& aCamera);
	bool OnScreen;

private:
	hgeSprite* mySprite;
	AABB myBoundingBox;
	CU::Vector2f myPosition;

};

