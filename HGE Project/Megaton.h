#ifndef _MEGATON_H_
#define _MEGATON_H_

#include "AudioSystem\AudioSystem.h"

#include "CommonUtilities\TimerManager.h"
#include "CommonUtilities\DL_Assert.h"
#include "CommonUtilities\Vector.h"

#include "GUI/GUIManager.h"

#include "InputManager.h"

#include "Renderer/RenderManager.h"
#include "ResourceManager.h"

#include "Settings.h"

#include "TriggerSystem/TriggerManager.h"

class HGE;
class GameState;
namespace CommonUtilities { class TimerManager; }
namespace CU = CommonUtilities;

class Megaton
{
	public:
		static void Create(HGE* aHGE, Renderer* aRenderer, const CU::Vector2i& aResolution);
		static void Destroy();
		static void Update(GameState* aGameState);
		
		static InputManager*		GetInputManager				();
		static ResourceManager*		GetResourceManager			();
		static RenderManager*		GetRenderManager			();
		static CU::TimerManager*	GetTimerManager				();
		static GUIManager*			GetGUIManager				();
		static TriggerManager*		GetTriggerManager			();
		static AudioSystem*			GetAudioSystem				();
		static Settings*			GetSettings					();

	private:
									Megaton						(void);
									~Megaton					(void);

		static Megaton*				myInstance					;

		InputManager*				myInputManager				;
		ResourceManager*			myResourceManager			;
		RenderManager*				myRenderManager				;
		CU::TimerManager*			myTimerManager				;
		GUIManager*					myGUIManager				;
		TriggerManager*				myTriggerManager			;
		AudioSystem*				myAudioSystem				;
		Settings*					mySettings					;
};

#endif