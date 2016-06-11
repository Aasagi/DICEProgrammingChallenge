#ifndef _TRIGGER_H
#define _TRIGGER_H

#include "CommonUtilities/Vector2decl.h"

enum class eTriggerType
{
	eQuitGame,
	ePushMainState,
	ePopMainState,
	ePushSubState,
	ePopSubState,
};

class GameState;
class Player;

struct Trigger
{
	eTriggerType		myTriggerType;
	GameState*			myGameState;
};

#endif