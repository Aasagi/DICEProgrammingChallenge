#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "GUI/Widget.h"
#include "CommonUtilities\Stack.h"
#include "CommonUtilities\GrowingArray.h"

class Widget;

class GameState
{
public:
	virtual void		Init();
	virtual void		Update();
	virtual void		HandleInput() = 0;
	virtual void		HandleInputWithoutGUI() = 0;

	inline void			PushGameState(GameState* aGameState);
	inline GameState*	PopGameState();

	inline bool			HasSubStates();

	inline CU::GrowingArray<Widget*>& GetMainWidgets();
	inline GameState*	GetSubState();

protected:
	GameState(void);
	virtual ~GameState(void);
	//CU::Stack<GameState*>		mySubStates;
	CU::GrowingArray<GameState*, int>mySubStates;
	CU::GrowingArray<Widget*>	myWidgets;
};

inline void GameState::PushGameState(GameState* aGameState)
{
	//mySubStates.Push(aGameState);
	mySubStates.Add(aGameState);
}

inline GameState* GameState::PopGameState()
{
	//return mySubStates.Pop();
	GameState* gameStateToReturn = mySubStates.GetLast();
	mySubStates.RemoveCyclicAtIndex(mySubStates.Size() - 1);
	return gameStateToReturn;
}

inline bool GameState::HasSubStates()
{
	return mySubStates.Size() > 0;
}

inline CU::GrowingArray<Widget*>& GameState::GetMainWidgets()
{
	return myWidgets;
}

inline GameState* GameState::GetSubState()
{
	//return mySubStates.Top();
	if (mySubStates.Size() == 0)
	{
		return nullptr;
	}
	return mySubStates.GetLast();
}

#endif