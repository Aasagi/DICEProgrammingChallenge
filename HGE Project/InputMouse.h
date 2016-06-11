#ifndef INPUTMOUSE_H
#define INPUTMOUSE_H

#include "CommonUtilities\Vector2.h"

class HGE;
class Level;
class InputMouse
{
public:
	friend class InputManager;
	void Update();
	CU::Vector2f& GetPosition();
	CU::Vector2f& GetDelta();
	short GetMouseWheel();
private:
	InputMouse(HGE* aEngine);
	~InputMouse(void);

	HGE* myEngine;
	CU::Vector2f myOldPosition;
	CU::Vector2f myCurrentPosition;
	CU::Vector2f myDelta;
};

#endif