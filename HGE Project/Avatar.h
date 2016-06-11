#pragma once
#include "ResourceManager.h"
#include "CommonUtilities/Vector.h"

class Avatar
{
public:
	Avatar();
	~Avatar();

	void Init();
	void Render();
	void Update();
	void HandleInput();

private:
	CU::Vector2f myPosition;

	hgeSprite* mySprite;
};

