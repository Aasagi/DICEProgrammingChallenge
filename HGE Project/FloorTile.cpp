#include "stdafx.h"
#include "FloorTile.h"
#include "SpriteRenderCommand.h"
#include "Megaton.h"
#include "hgesprite.h"

FloorTile::FloorTile()
{
	myFloorSprite = Megaton::GetResourceManager()->GetSprite("Data/node.png");
	myBoundingBox = AABB(10.0f, 10.0f, 10.0f, 10.0f);
};


FloorTile::~FloorTile()
{
}

SpriteRenderCommand* FloorTile::GetRenderCommand()
{
	return new SpriteRenderCommand(myFloorSprite, myPosition);
}
