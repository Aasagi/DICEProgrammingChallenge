#include "Renderer.h"
#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include <Windows.h>
#include "CommonUtilities/DL_Assert.h"

Renderer::Renderer()
{
	myRenderCommands = nullptr;
	myRenderDone = true;
	myShutdownThread = false;
	myClearScene = false;
}

Renderer::Renderer(HGE* aHGE) :myHGE(aHGE)
{
	myRenderCommands = nullptr;
	myRenderDone = true;
	myShutdownThread = false;
}

Renderer::~Renderer(void)
{
	myRenderCommands->DeleteAll();
}

void Renderer::Init(HGE* aHGE)
{
	myHGE = aHGE;
}

void Renderer::ThreadedUpdate()
{
	while (myShutdownThread == false)
	{
		while (myRenderDone == true)
		{
			Sleep(1);
		};

		myHGE->Gfx_BeginScene();
		myHGE->Gfx_Clear(0xffffffff);
		while (0 < myRenderCommands->Count())
		{
			RenderCommand* command = myRenderCommands->Dequeue();
			command->Draw();
			delete command;
		}
		myHGE->Gfx_EndScene();

		SetRenderIsDone(true);
	}
}