#ifndef INPUTMANAGER_H
#define INPUTMANGER_H

#include <map>
#include "InputButton.h"
#include "InputMouse.h"

class HGE;
class InputManager
{
	friend class Megaton;
public:
	bool ButtonPressed(eButton aButton);
	bool ButtonReleased(eButton aButton);
	bool ButtonIsDown(eButton aButton);
	InputMouse& GetMouse();
	void Update();

	inline static InputManager* GetInstance();

private:
	InputManager(HGE* aEngine);
	~InputManager(void);

	HGE* myEngine;
	InputMouse myMouse;
	std::map<eButton, InputButton> myButtons;
};


#endif