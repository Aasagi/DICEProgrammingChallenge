#include "stdafx.h"
#include "FloorTile.h"
#include "SpriteRenderCommand.h"
#include "Megaton.h"
#include "hgesprite.h"
#include "Defines.h"

FloorTile::FloorTile()
{
	myFloorSprite = Megaton::GetResourceManager()->GetSprite("Data/node.png");
	Recalculate(1);
};

FloorTile::~FloorTile()
{
}

void FloorTile::Recalculate(int tileHeight)
{
	myTileHeight = tileHeight;
	myBoundingBox = AABB(myTileHeight * TILE_SIZE * 0.5f, myTileHeight * TILE_SIZE * 0.5f, myTileHeight * TILE_SIZE * 0.5f, myTileHeight * TILE_SIZE * 0.5f);
}

int FloorTile::GetTileHeight()
{
	return myTileHeight;
}


void FloorTile::Render()
{
	for (int tileHeightIndex = 0; tileHeightIndex < myTileHeight; tileHeightIndex++)
	{
		Megaton::GetRenderManager()->AddCommand(new SpriteRenderCommand(myFloorSprite, myPosition - CU::Vector2f(0.0f, tileHeightIndex * TILE_SIZE)));
	}
}

AABB FloorTile::GetAABB() const
{
	return myBoundingBox;
}

