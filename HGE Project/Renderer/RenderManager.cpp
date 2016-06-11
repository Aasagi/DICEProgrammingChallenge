#include "stdafx.h"
#include "RenderManager.h"
#include "CommonUtilities\Vector.h"
#include "CommonUtilities/DL_Assert.h"

RenderManager* RenderManager::myInstance = nullptr;

RenderManager::RenderManager(Renderer* someRenderer)
{
	myRenderer = someRenderer;
	myRenderCommandsToFill = &myFirstRenderCommands;
	myRenderer->SetRenderBuffert(myRenderCommandsToFill);
}

RenderManager::~RenderManager(void)
{
	myFirstRenderCommands.DeleteAll();
	mySecondRenderCommands.DeleteAll();
}

void RenderManager::Create(Renderer* someRenderer)
{
	myInstance = new RenderManager(someRenderer);
}

void RenderManager::Update()
{
	assert(myRenderer != nullptr && "Need to call RenderManager::Init(Renderer* someRenderer) before calling RenderManager::Update()");
	SwapRendererCommands();
}

void RenderManager::AddCommand(RenderCommand* someCommand)
{
	someCommand->SetPosition(someCommand->GetPosition()/* - (Camera::GetInstance()->GetPosition())*/);
	myRenderCommandsToFill->Enqueue(someCommand);
}

void RenderManager::SwapRendererCommands()
{
	while(myRenderer->IsRenderDone() == false);

	if(myRenderCommandsToFill == &myFirstRenderCommands)
	{
		myRenderer->SetRenderBuffert(&myFirstRenderCommands);
		myRenderCommandsToFill = &mySecondRenderCommands;
	}
	else if(myRenderCommandsToFill == &mySecondRenderCommands)
	{
		myRenderer->SetRenderBuffert(&mySecondRenderCommands);
		myRenderCommandsToFill = &myFirstRenderCommands;
	}

	myRenderer->SetRenderIsDone(false);
}

