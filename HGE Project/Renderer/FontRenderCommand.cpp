#include "../stdafx.h"
#include "FontRenderCommand.h"
#include "hgefont.h"



FontRenderCommand::FontRenderCommand(std::string aString, hgeFont* aFont, float aX, float aY, char aAlignment)
{
	myString = aString;
	myFont = aFont;
	myPosition.myX = aX;
	myPosition.myY = aY;
	myAlignment = aAlignment;
}
FontRenderCommand::FontRenderCommand(std::string aString, hgeFont* aFont, CU::Vector2<float> aPosition, char aAlignment)
{
	myString = aString;
	myFont = aFont;
	myPosition = aPosition;
	myAlignment = aAlignment;
}
FontRenderCommand::~FontRenderCommand(void)
{
}

void FontRenderCommand::Draw()
{
	myFont->SetScale(myScaleH);
	myFont->SetRotation(myRotation);
	myFont->SetColor(myColor);
	myFont->Render(myPosition.x, myPosition.y, myAlignment, myString.c_str());
}

void FontRenderCommand::SetString(const std::string& someString)
{
	myString = someString;
}
