#include "GUIManager.h"
#include "../Megaton.h"
#include "../GameState.h"
#include "Widget.h"

GUIManager* GUIManager::myInstance = nullptr;

GUIManager::GUIManager()
{
}

GUIManager::~GUIManager()
{

}

void GUIManager::Update(GameState* aGameState)
{
	bool hasSubStack = false;
	if(aGameState->HasSubStates() == true)
	{
		hasSubStack = true;
	}
	if(hasSubStack == true)
	{
		Update(aGameState->GetSubState());
	}
	else
	{
		//This wont work if it's Mainstate->SubState->Substate
		if(myFocusedWidget != nullptr)
		{
			//If the focusedwidget did not managed to get drawn, it means it isn't on the screen and
			//it is pointless to continue focusing on that respective widget
			if(myFocusedWidget->HasBeenDrawn() == false)
			{
				myFocusedWidget = nullptr;
			}
			else
			{
				myFocusedWidget->ResetDrawnFlag();
			}
		}
	}

	UpdateWidgets(aGameState->GetMainWidgets());
}

void GUIManager::UpdateWidgets(CU::GrowingArray<Widget*>& someWidgets)
{
	//CU::GrowingArray<Widget*>& widgets = aGameState->GetMainWidgets();
	Widget* widget = nullptr;
	for(unsigned short i = 0; i < someWidgets.Size(); ++i)
	{
		widget = someWidgets[i];

		//Now, is the mouse inside the widget?
		if(widget->Inside(Megaton::GetInputManager()->GetMouse().GetPosition()) == true)
		{
			//It is! Tell the manager to say that the event is on focus!
			widget->Notify(eGUIEvent::eMouseHover);
			myFocusedWidget = widget;

			if(Megaton::GetInputManager()->ButtonPressed(eButton::eLEFTMOUSE) == true)
			{
				widget->Notify(eGUIEvent::eMouseDown);
			}
			if(Megaton::GetInputManager()->ButtonIsDown(eButton::eLEFTMOUSE) == true)
			{
				if(widget->HasFocus() == true)
				{
					widget->Notify(eGUIEvent::eMouseDown);
				}
			}
			if(Megaton::GetInputManager()->ButtonReleased(eButton::eLEFTMOUSE) == true)
			{
				if(widget->HasFocus() == true)
				{
					widget->Notify(eGUIEvent::eMouseClick);
				}
			}
		}
		else
		{
			widget->Notify(eGUIEvent::eMouseNotHover);
		}

		if(Megaton::GetInputManager()->ButtonReleased(eButton::eLEFTMOUSE) == true)
		{
			widget->Notify(eGUIEvent::eMouseUp);
		}

		widget->Draw();
	}

	if(myFocusedWidget != nullptr)
	{
		if(myFocusedWidget->Inside(Megaton::GetInputManager()->GetMouse().GetPosition()) == false)
		{
			myFocusedWidget->Notify(eGUIEvent::eMouseNotHover);
			if(myFocusedWidget->HasFocus() == false)
			{
				myFocusedWidget = nullptr;
			}
		}
	}
}

bool GUIManager::HasWidgetFocus() const
{
	if(myFocusedWidget != nullptr)
	{
		return myFocusedWidget->HasFocus();
	}

	return false;
}