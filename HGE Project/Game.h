#ifndef _GAME_H_
#define _GAME_H_

#include "GameState.h"
#include "TriggerObserver.h"
#include "FloorTile.h"
#include "Avatar.h"
#include "Camera.h"

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

	void Notify(const eTriggerType& aTriggerType, void* aTrigger) override;

private:
	CU::GrowingArray<FloorTile>		myFloorTiles;

	float myUpdateTimer;

	Avatar myPlayer;

	Camera myCamera;
	void GenerateRandomFloor();

	hgeSprite* myBackground1;
	hgeSprite* myBackground2;
};

#endif