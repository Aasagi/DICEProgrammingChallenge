#ifndef _SPRITE_RENDER_COMMAND_H_
#define _SPRITE_RENDER_COMMAND_H_

#include "RenderCommand.h"

class hgeSprite;

class SpriteRenderCommand : public RenderCommand
{
	public:
		SpriteRenderCommand(hgeSprite* aSprite, float aX, float aY);
		SpriteRenderCommand(hgeSprite* aSprite, CU::Vector2<float> aPosition);
		~SpriteRenderCommand(void);

		void Draw() override;

		void SetSprite(hgeSprite* someSprite);

	private:
		hgeSprite* mySprite;
};

#endif