#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include "CommonUtilities\GrowingArray.h"

class GameState;
class Widget;

class GUIManager
{
public:
	friend class Megaton;

	void							Update(GameState* aGameState);
	void							UpdateWidgets(CU::GrowingArray<Widget*>& someWidgets);
	bool							HasWidgetFocus() const;

private:
	GUIManager();
	~GUIManager();

	static GUIManager*				myInstance;

	int								myGameState;
	Widget*							myFocusedWidget;
};

#endif