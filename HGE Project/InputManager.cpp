#include "stdafx.h"
#include "InputManager.h"
#include "hge.h"

InputManager::InputManager(HGE* aEngine)
	:myMouse(aEngine)
{
	myEngine = aEngine;
	myButtons[eButton::eLEFTMOUSE].myButton = eButton::eLEFTMOUSE;
	myButtons[eButton::eMIDDLEMOUSE].myButton = eButton::eMIDDLEMOUSE;
	myButtons[eButton::eRIGHTMOUSE].myButton = eButton::eRIGHTMOUSE;
}


InputManager::~InputManager(void)
{
}

bool InputManager::ButtonPressed(eButton aButton)
{
	if (!myButtons.count(aButton))
	{
		myButtons[aButton].myButton = aButton;
	}
	if (myButtons[aButton].myCurrentState == true && myButtons[aButton].myLastState == false)
	{
		return true;
	}
	return false;
}
bool InputManager::ButtonReleased(eButton aButton)
{
	if (!myButtons.count(aButton))
	{
		myButtons[aButton].myButton = aButton;
		return false;
	}
	if (myButtons[aButton].myCurrentState == false && myButtons[aButton].myLastState == true)
	{
		return true;
	}
	return false;
}
bool InputManager::ButtonIsDown(eButton aButton)
{
	if (!myButtons.count(aButton))
	{
		myButtons[aButton].myButton = aButton;
	}
	return myButtons[aButton].myCurrentState;
}
void InputManager::Update()
{
	myMouse.Update();
	for (auto it = myButtons.begin(); it != myButtons.end(); ++it)
	{
		it->second.myLastState = it->second.myCurrentState;
		it->second.myCurrentState = myEngine->Input_GetKeyState(static_cast<int>(it->second.myButton));
	}
}

InputMouse& InputManager::GetMouse()
{
	return myMouse;
}