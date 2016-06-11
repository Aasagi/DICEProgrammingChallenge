#include "Button.h"
#include "../Megaton.h"
#include "hgesprite.h"
#include "../Renderer\SpriteRenderCommand.h"

Button::Button()
{
	myZ = -100;
}

Button::Button(const Button* aButton) : Widget(aButton)
{
	myActiveState = aButton->myActiveState;
}

Button::~Button()
{

}

void Button::Init()
{
	assert(myInit == false && "You have already called Init() on this Button!");
	std::function<void()> mouseHover = [this]()
	{
		SetSpriteState(eWidgetState::eHover);
		myHasFocus = true;
	};

	std::function<void()> mouseNotHover = [this]()
	{
		SetSpriteState(eWidgetState::eNormal);

		if(myOnPressedFlag == false)
		{
			myHasFocus = false;
		}

		if(myActiveState == true)
		{
			SetSpriteState(eWidgetState::eOnPressed);
		}
	};

	std::function<void()> mouseDown = [this]()
	{
		SetSpriteState(eWidgetState::eOnPressed);
		myOnPressedFlag = true;
	};

	std::function<void()> mouseUp = [this]()
	{
		SetSpriteState(eWidgetState::eNormal);
		myHasFocus = false;
	};
	
	this->AddWidgetEvent(eGUIEvent::eMouseHover, mouseHover);
	this->AddWidgetEvent(eGUIEvent::eMouseNotHover, mouseNotHover);
	this->AddWidgetEvent(eGUIEvent::eMouseDown, mouseDown);
	this->AddWidgetEvent(eGUIEvent::eMouseUp, mouseUp);

	myActiveState = false;
	myInit = true;
}

void Button::Draw()
{
	assert(myInit == true && "Button has not been Initialized!");

	CU::Vector2f scaling = myPosition / Megaton::GetSettings()->myWindowResolution;

	SpriteRenderCommand* command = new SpriteRenderCommand(mySprites[myState], myPosition.x, myPosition.y);
	command->SetZ(myZ);
	Megaton::GetRenderManager()->AddCommand(command);
	myHasBeenDrawn = true;
}