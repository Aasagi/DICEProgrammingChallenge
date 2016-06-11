#ifndef WIDGET_H
#define WIDGET_H

#include <map>
#include <functional>
#include "CommonUtilities/DL_Assert.h"
#include "CommonUtilities/Vector2.h"
#include "CommonUtilities/AABB.h"

enum eGUIEvent
{
	eMouseHover,
	eMouseNotHover,
	eMouseClick,
	eMouseDown,
	eMouseUp,
};

enum eWidgetState
{
	eNormal,
	eHover,
	eOnPressed,
};

class hgeSprite;

class Widget
{
public:
	Widget()
	{
		myInit			= false;
		myEvents;
		myPosition;
		myHitBox		= AABB(-1,-1,-1,-1);
		mySprites;
		myState			= eWidgetState::eNormal;
		myHasFocus		= false;
		myOnPressedFlag	= false;
		myZ				= -100;
		myHasBeenDrawn	= false;
	}
	Widget(const Widget* aWidget)
	{
		myInit			= aWidget->myInit;

		myEvents		= aWidget->myEvents;

		myPosition		= aWidget->myPosition;
		myHitBox		= aWidget->myHitBox;
		mySprites		= aWidget->mySprites;
		myState			= aWidget->myState;
		myHasFocus		= aWidget->myHasFocus;
		myOnPressedFlag	= aWidget->myOnPressedFlag;
		myZ				= aWidget->myZ;
		myHasBeenDrawn	= aWidget->myHasBeenDrawn;
	}
	~Widget(){}

	//virtual void		Update				() = 0;
	virtual void		Init				() = 0;
	virtual void		Draw				() = 0;

	inline void			AddWidgetEvent		(const eGUIEvent& aState, std::function<void()> aFunction);
	inline void			ReplaceWidgetEvent	(const eGUIEvent& aState, std::function<void()> aFunction);

	inline void			AddSprite			(const eWidgetState& aState, hgeSprite* aSprite);

	inline void			SetPosition			(const CU::Vector2f& aPosition);
	inline void			SetAABB				(const AABB& aHitBox);
	inline CU::Vector2f	GetPosition			() const;
	inline AABB			GetAABB				() const;

	inline void			SetSpriteState		(const eWidgetState& aState);

	inline void			GotFocus			();
	inline bool			HasFocus			();
	inline void			LostFocus			();

	inline void			SetZ				(const float& aZ);
	inline float		GetZ				() const;

	inline bool			Inside				(const CU::Vector2f& aMousePos);
	inline void			ResetDrawnFlag		();
	inline bool			HasBeenDrawn		() const;

	inline void			Notify				(const eGUIEvent& anEvent);

protected:
	bool											myInit;
	std::map<eGUIEvent, std::function<void()> >		myEvents;
	CU::Vector2f									myPosition;		//Position of the actual widget
	AABB											myHitBox;		//X and Y is Offset

	std::map<eWidgetState, hgeSprite*>				mySprites;
	eWidgetState									myState;
	bool											myHasFocus;
	bool											myOnPressedFlag;
	float											myZ;
	bool											myHasBeenDrawn;
};

inline bool operator<(const Widget& aWidget, const Widget& aWidgetToCompare)
{
	if(aWidget.GetZ() < aWidgetToCompare.GetZ())
	{
		return true;
	}

	return false;
}

inline void Widget::AddWidgetEvent(const eGUIEvent& aState, std::function<void()> aFunction)
{
	assert(myEvents.find(aState) == myEvents.end() && "Widget function already loaded! State is occupied!");

	myEvents[aState] = aFunction;
}

inline void Widget::ReplaceWidgetEvent(const eGUIEvent& aState, std::function<void()> aFunction)
{
	assert(myEvents.find(aState) != myEvents.end() && "Widget function not loaded! State is empty!");

	myEvents[aState] = aFunction;
}

inline void Widget::AddSprite(const eWidgetState& aState, hgeSprite* aSprite)
{
	assert(mySprites.find(aState) == mySprites.end() && "Widget Sprite already loaded! State is occupied!");

	mySprites[aState] = aSprite;
}

inline void Widget::SetPosition(const CU::Vector2f& aPosition)
{
	myPosition = aPosition;
}

inline void Widget::SetAABB(const AABB& aHitBox)
{
	myHitBox = aHitBox;
}

inline CU::Vector2f	Widget::GetPosition() const
{
	return myPosition;
}

inline AABB Widget::GetAABB() const
{
	return myHitBox;
}

inline void Widget::SetSpriteState(const eWidgetState& aState)
{
	myState = aState;
}

inline void Widget::GotFocus()
{
	myHasFocus = true;
}

inline bool Widget::HasFocus()
{
	return myHasFocus;
}

inline void Widget::LostFocus()
{
	myHasFocus = false;
}

inline void Widget::SetZ(const float& aZ)
{
	assert(aZ < 0 && "Cannot assign a Z value larger or equal to 0! Widget::SetZ()");
	myZ = aZ;
}

inline float Widget::GetZ() const
{
	return myZ;
}

bool Widget::Inside(const CU::Vector2f& aMousePos)
{
	//Since the X and Y on myHitBox only has Offset and Dimension,
	//We have to add the position of the widget, so we can calculate if the mousePos was inside
	AABB hitBoxRelativeToCamera = myHitBox;
	hitBoxRelativeToCamera.SetX(myHitBox.GetX() + myPosition.x);
	hitBoxRelativeToCamera.SetY(myHitBox.GetY() + myPosition.y);

	return hitBoxRelativeToCamera.Inside(aMousePos);
}

inline void Widget::ResetDrawnFlag()
{
	myHasBeenDrawn = false;
}

inline bool Widget::HasBeenDrawn() const
{
	return myHasBeenDrawn;
}

inline void Widget::Notify(const eGUIEvent& anEvent)
{
	assert(myInit == true && "Button has not been Initialized!");
	if(myEvents.find(anEvent) != myEvents.end())
	{
		myEvents[anEvent]();
	}
}

#endif