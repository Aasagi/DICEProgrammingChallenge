#include "SpriteRenderCommand.h"
#include "hgesprite.h"
#include <math.h>

SpriteRenderCommand::SpriteRenderCommand(hgeSprite* aSprite, CU::Vector2<float> aPosition)
{
	mySprite = aSprite;
	myPosition = aPosition;
}

SpriteRenderCommand::SpriteRenderCommand(hgeSprite* aSprite, float aX, float aY)
{
	mySprite = aSprite;
	myPosition.myX = aX;
	myPosition.myY = aY;
}
SpriteRenderCommand::~SpriteRenderCommand(void)
{
}

void SpriteRenderCommand::Draw()
{
	mySprite->SetColor(myColor);
	mySprite->RenderEx(floorf(myPosition.x), floorf(myPosition.y), myRotation, myScaleH, myScaleV);
}

void SpriteRenderCommand::SetSprite(hgeSprite* someSprite)
{
	mySprite = someSprite;
}
