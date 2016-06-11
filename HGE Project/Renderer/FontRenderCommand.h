#ifndef _FONT_RENDER_COMMAND_H_
#define _FONT_RENDER_COMMAND_H_

#include "rendercommand.h"
#include <string>

class hgeFont;
class FontRenderCommand : public RenderCommand
{
	public:
		FontRenderCommand(std::string aString, hgeFont* aFont, float aX, float aY, char aAlignment = 0);
		FontRenderCommand(std::string aString, hgeFont* aFont, CU::Vector2<float> aPosition, char aAlignment = 0);
		~FontRenderCommand(void);

		void Draw() override;

		void SetString(const std::string& someString);

	private:
		hgeFont* myFont;
		std::string myString;
		char myAlignment;
};

#endif