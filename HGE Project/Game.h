#ifndef _GAME_H_
#define _GAME_H_

#include "GameState.h"
#include "TriggerObserver.h"
#include "Square.h"
class hgeSprite;

class Game : public GameState, public TriggerObserver
{
public:
	Game(void);
	~Game(void);

	void Init() override;
	void Update() override;
	void Render();
	void HandleInput() override;
	void HandleInputWithoutGUI() override;
	int	 CountTaken(int aIndex);

	int FindIndex(int aX, int aY);


	bool CheckIfLineExists(CU::Vector2i aPosition, int aIndex);

	int WinCheck();

	void UpdateRandom();
	void UpdateChoice();
	void Notify(const eTriggerType& aTriggerType, void* aTrigger) override;

private:
	CU::GrowingArray<Square>		mySquare;
	CU::GrowingArray<bool>			mySquareOccupation;

	float myUpdateTimer;
	int myChoiceScore;
	int myRandomScore;
	
	bool myAITurn;
	bool myHasTakenASquare;

	hgeSprite* myNodeSprite;
	hgeSprite* myVertSprite;
	hgeSprite* myHoriSprite;
	hgeSprite* myCubeSprite;


};

#endif