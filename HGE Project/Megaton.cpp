#include "stdafx.h"
#include "Megaton.h"
#include "Renderer/FontRenderCommand.h"

#define CHECK_VALID_SINGLETON assert(myInstance != nullptr && "Megaton::Create(HGE* aHGE) has not been called!");

Megaton* Megaton::myInstance = nullptr;

Megaton::Megaton(void)
{
	myResourceManager = nullptr;
	myTimerManager = nullptr;
	myGUIManager = nullptr;
	myInputManager = nullptr;
	myTriggerManager = nullptr;
	myAudioSystem = nullptr;
	mySettings = nullptr;
}

Megaton::~Megaton(void) { }

void Megaton::Create(HGE* aHGE, Renderer* aRenderer, const CU::Vector2i& aResolution)
{
	assert(myInstance == nullptr && "Megaton::Create(HGE* aHGE) has already been called!");
	myInstance = new Megaton();

	myInstance->myResourceManager = new ResourceManager(aHGE);
	myInstance->myTimerManager = new CU::TimerManager();
	myInstance->myRenderManager = new RenderManager(aRenderer);
	myInstance->myInputManager = new InputManager(aHGE);
	myInstance->myTriggerManager = new TriggerManager();
	myInstance->myGUIManager = new GUIManager();
	myInstance->myAudioSystem = new AudioSystem();
	myInstance->myAudioSystem->Init(64, 100.f);
	myInstance->mySettings = new Settings(CU::Vector2f(aResolution.x, aResolution.y));
}

void Megaton::Destroy()
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
#endif
	SAFE_DELETE(myInstance->myTimerManager);
	SAFE_DELETE(myInstance->myResourceManager);
	SAFE_DELETE(myInstance->myInputManager);
	SAFE_DELETE(myInstance->myGUIManager);
	SAFE_DELETE(myInstance->myTriggerManager);
	SAFE_DELETE(myInstance->myAudioSystem);
	SAFE_DELETE(myInstance->mySettings);
}

void Megaton::Update(GameState* aGameState)
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
	assert(myInstance->myInputManager != nullptr && "InputManager is not created!");
	assert(myInstance->myRenderManager != nullptr && "RenderManager is not created!");
	assert(myInstance->myTimerManager != nullptr && "TimerManager is not created!");
	assert(myInstance->myGUIManager != nullptr && "GUIManager is not created!");
	assert(myInstance->myTriggerManager != nullptr && "TriggerManager is not created!");
	assert(myInstance->myAudioSystem != nullptr && "AudioSystem is not created!");
	assert(myInstance->mySettings != nullptr && "Settings is not created!");
#endif
	myInstance->myInputManager->Update();
	myInstance->myRenderManager->Update();
	myInstance->myTimerManager->Update();
	myInstance->myGUIManager->Update(aGameState);
	myInstance->myTriggerManager->Update();
	myInstance->myAudioSystem->Update();
}

InputManager* Megaton::GetInputManager()
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
		assert(myInstance->myInputManager != nullptr && "InputManager is not created!");
#endif
	return myInstance->myInputManager;
}

ResourceManager* Megaton::GetResourceManager()
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
		assert(myInstance->myResourceManager != nullptr && "ResourceManager is not created!");
#endif
	return myInstance->myResourceManager;
}

RenderManager* Megaton::GetRenderManager()
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
		assert(myInstance->myRenderManager != nullptr && "RenderManager is not created!");
#endif
	return myInstance->myRenderManager;
}

CU::TimerManager* Megaton::GetTimerManager()
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
		assert(myInstance->myTimerManager != nullptr && "TimerManager is not created!");
#endif
	return myInstance->myTimerManager;
}

GUIManager* Megaton::GetGUIManager()
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
		assert(myInstance->myGUIManager != nullptr && "GUIManager is not created!");
#endif
	return myInstance->myGUIManager;
}

TriggerManager* Megaton::GetTriggerManager()
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
		assert(myInstance->myTriggerManager != nullptr && "TriggerManager is not created!");
#endif
	return myInstance->myTriggerManager;
}

AudioSystem* Megaton::GetAudioSystem()
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
		assert(myInstance->myAudioSystem != nullptr && "AudioSystem is not created!");
#endif
	return myInstance->myAudioSystem;
}

Settings* Megaton::GetSettings()
{
#if defined(_DEBUG) || defined(NDEBUG)
	CHECK_VALID_SINGLETON
		assert(myInstance->mySettings != nullptr && "Settings is not created!");
#endif
	return myInstance->mySettings;
}