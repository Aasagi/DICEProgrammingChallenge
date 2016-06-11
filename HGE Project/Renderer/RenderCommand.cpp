#include "RenderCommand.h"

RenderCommand::RenderCommand()
{
	myColor = 0xffffffff;
	myZ = -0.f;
	myScaleV = 0;
	myRotation = 0;
	myScaleH = 1;
	myScaleV = 0;
}

RenderCommand::~RenderCommand()
{

}

bool RenderCommand::operator>(const RenderCommand& aCommand)
{
	if (myZ > aCommand.myZ)
	{
		return true;
	}
	return false;
}

bool RenderCommand::operator<(const RenderCommand& aCommand)
{
	if (myZ < aCommand.myZ)
	{
		return true;
	}
	return false;
}

bool RenderCommand::operator>=(const RenderCommand& aCommand)
{
	if (myZ >= aCommand.myZ)
	{
		return true;
	}
	return false;
}

bool RenderCommand::operator<=(const RenderCommand& aCommand)
{
	if (myZ <= aCommand.myZ)
	{
		return true;
	}
	return false;
}

void RenderCommand::SetPosition(const CU::Vector2<float>& somePosition)
{
	myPosition = somePosition;
}
void RenderCommand::SetColor(unsigned long aColor)
{
	myColor = aColor;
}
void RenderCommand::SetZ(float aZ)
{
	myZ = aZ;
}

void RenderCommand::SetScaleH(const float& aScale)
{
	myScaleH = aScale;
}

void RenderCommand::SetScaleV(const float& aScale)
{
	myScaleV = aScale;
}
void RenderCommand::SetRotation(const float& aRotation)
{
	myRotation = aRotation;
}

void RenderCommand::Draw(){}
