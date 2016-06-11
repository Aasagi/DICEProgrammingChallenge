#ifndef WIDGET_BUTTON_H
#define WIDGET_BUTTON_H

#include "Widget.h"

class Button : public Widget
{
public:
	Button();
	Button(const Button* aButton);
	~Button();

	//void	Update() override;
	void	Init() override;
	void	Draw() override;
	inline void	SetActiveState(const bool& aState);

private:
	bool	myActiveState;
};

inline void Button::SetActiveState(const bool& aState)
{
	myActiveState = aState;
}

#endif