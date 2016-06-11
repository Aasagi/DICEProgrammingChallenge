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
	myBoundingBox = AABB(myPosition.x, myPosition.y - ( TILE_SIZE * ( max(0, tileHeight - 1))), TILE_SIZE, TILE_SIZE * tileHeight);
}

int FloorTile::GetTileHeight()
{
	return myTileHeight;
}


void FloorTile::Render(Camera& aCamera)
{
	for (int tileHeightIndex = 0; tileHeightIndex < myTileHeight; tileHeightIndex++)
	{
		Megaton::GetRenderManager()->AddCommand(new SpriteRenderCommand(myFloorSprite, aCamera.ConvertPositionToCameraPosition(myPosition - CU::Vector2f(0.0f, tileHeightIndex * TILE_SIZE))));
	}
}

void FloorTile::SetPosition(CU::Vector2f aPosition)
{
	myPosition = aPosition;
	Recalculate(GetTileHeight());
}

CU::Vector2f FloorTile::GetPosition() const
{
	return myPosition;
}


AABB FloorTile::GetAABB() const
{
	return myBoundingBox;
}

