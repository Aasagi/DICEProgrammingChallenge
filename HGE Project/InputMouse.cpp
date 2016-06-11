#include "stdafx.h"
#include "InputMouse.h"
#include "hge.h"

InputMouse::InputMouse(HGE* aEngine)
{
	myEngine = aEngine;
}


InputMouse::~InputMouse(void)
{
}

void InputMouse::Update()
{
	myOldPosition = myCurrentPosition;
	myEngine->Input_GetMousePos(&myCurrentPosition.x, &myCurrentPosition.y);
	myDelta = myCurrentPosition - myOldPosition;
}

CU::Vector2f& InputMouse::GetPosition()
{
	return myCurrentPosition;
}

CU::Vector2f& InputMouse::GetDelta()
{
	return myDelta;
}

short InputMouse::GetMouseWheel()
{
	hgeInputEvent* wheelEvent = new hgeInputEvent;
	while (myEngine->Input_GetEvent(wheelEvent))
	{
		if (wheelEvent->type == INPUT_MOUSEWHEEL)
		{
			return static_cast<short>(wheelEvent->wheel);
		}
	}
	return 0;
}