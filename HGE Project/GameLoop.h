#ifndef _GAME_LOOP_H_
#define _GAME_LOOP_H_

#include <Windows.h>	//needed for MSG
#include <thread>
#include "GameState.h"
#include "CommonUtilities\Stack.h"
#include "Renderer\Renderer.h"
#include "TriggerSystem\TriggerObserver.h"

namespace CU = CommonUtilities;

class Game;
class HGE;
class GameLoop : public TriggerObserver
{
	public:
		GameLoop(void);
		~GameLoop(void);

		void Init(HGE* aHGE, const CU::Vector2i& aResolution);
		void Run();

		void Notify(const eTriggerType& aTriggerType, void* aTrigger) override;

	private:
		void Update();
		bool ReadHgeMSG();

		HGE* myHGE;
		MSG myWindowMessage;

		CU::Stack<GameState*> myStateStack;
		Game* myGame;

		bool myGameIsRunning;
		volatile bool myRenderUsDone;
		volatile bool myGameIsLoaded;

		std::thread* myRenderThread;
		Renderer myRenderer;
};

#endif